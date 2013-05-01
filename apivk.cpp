/***************************************
 * Joly. Connect your web and your computer in the one place.
 * Copyright (C) 2012-2013 Ivan Akulov <gxoptg@gmail.com>
 *
 * This file is the part of Joly.
 *
 * Joly is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Joly is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Joly. If not, see <http://www.gnu.org/licenses/>.
 **************************************/

#include "apivk.h"
#include <QtWidgets>
#include <QWebView>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkCookie>
#include <QtNetwork/QNetworkCookieJar>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QUrl>
#include <QtXml>
#include <QVariant>
#include <QDateTime>
#include <QDebug>
#include "ostools.h"
#include "consts.h"
#include "apivkdirect.h"
#include "apivkauth.h"

#ifdef Q_OS_WIN
#include <QJson/include/QJson/Parser>
#elif defined(Q_OS_LINUX)
#include <qjson/parser.h>
#endif

#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif


    // defining static class members


    // defining class methods

ApiVK::ApiVK(QObject *parent) :
    QObject(parent), m_auth()
{
    connect(&m_auth, SIGNAL(authorisationSucceed(QString)), &m_directApi, SLOT(setAccessToken(QString)));
    connect(&m_auth, SIGNAL(authorisationSucceed(QString)), &m_uploader, SLOT(setAccessToken(QString)));
    connect(&m_auth, SIGNAL(authorisationSucceed(QString)), SIGNAL(authorisationSucceed()));
    connect(&m_auth, SIGNAL(authorisationFailed(QString,QString)), SIGNAL(authorisationFailed(QString,QString)));
    connect(&m_directApi, SIGNAL(requestFinished(QByteArray)), SLOT(handleRequestFinish(QByteArray)));
    connect(&m_directApi, SIGNAL(requestFailed(int,QString)), SIGNAL(requestFailed(int,QString)));
}

void ApiVK::getUnreadMessagesVariationRequest(int *errorCode) {
        // посылает запрос на получение количества непрочитанных сообщений
    if (!m_auth.isAuthorised()) {
        if (errorCode) *errorCode = DidntAuthorised;
        return;
    }

    if (!m_lpsData.initialized) {
        m_directApi.messages_get(1);

        QUrl url("https://api.vk.com/method/messages.getLongPollServer");
        url.addQueryItem("access_token", m_auth.getAccessToken());

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        manager->get(QNetworkRequest(url));
        connect(manager, SIGNAL(finished(QNetworkReply*)),  SLOT(special_longPollServerDataReturned(QNetworkReply*)));
    } else {
        m_directApi.askLongPollServer(m_lpsData.serverAddress, m_lpsData.key, m_lpsData.ts);
    }
}


void ApiVK::special_longPollServerDataReturned(QNetworkReply* reply) {
    if (reply->error())
        return;

    QByteArray content = reply->readAll();
    reply->deleteLater();

    QJson::Parser parser;
    bool ok;

    QVariantMap lpsData = parser.parse(content, &ok).toMap();
    Q_ASSERT_X(ok, "LongPollServer data analysing", "parser returned error");
    if (Q_UNLIKELY(!ok)) {
        qWarning() << tr("LongPollServer data analysing: parser returned an error.");
        return;
    }

    if (lpsData.contains("response")) {
        QVariantMap nestedData = lpsData.value("response").toMap();
        m_lpsData.key = nestedData.value("key").toString();
        m_lpsData.serverAddress = nestedData.value("server").toString().replace(QString("\\/"), QChar('/'));
        m_lpsData.ts = nestedData.value("ts").toString();
        m_lpsData.initialized = true;

            // Why i'm using value() instead of []? Because it's more safe and QtCreator gives hints for results of value() function.
    }

//    getUnreadMessagesRequest();
}

int ApiVK::getUnreadMessagesVariation(int *errorCode) {
        // возвращает результат выполнения функции getUnreadMessagesRequest()
        // при возникновении ошибки возвращает -1 и код ошибки в errorCode (если передана)
    if (!m_auth.isAuthorised()) {
        if (errorCode) *errorCode = DidntAuthorised;
        return -1;
    }


    QJson::Parser parser;
    bool ok;

    QVariantMap returnedData = parser.parse(m_returnedData, &ok).toMap();
    Q_ASSERT_X(ok, "Messages data analysing", "parser returned error");
    if (Q_UNLIKELY(!ok)) {
        qWarning() << tr("Messages data analysing: parser returned an error. Couldn't get unread messages count.");

        if (errorCode) *errorCode = AnalysisError;
        return -1;
    }

    // if it's result of messages.get
    if (returnedData.contains("response")) {
        return returnedData.value("response").toList().first().toInt();
    }
    else {
        m_lpsData.ts = returnedData.value("ts").toString();
        QVariantList updates = returnedData.value("updates").toList();

        int count = 0;
        const short int newMessage = 4;
        const short int messageWasRead = 3;
        const short int messageWasReadMask = 1;
        for (QVariantList::ConstIterator iter = updates.begin(); iter != updates.end(); ++iter) {
            QVariantList nestedList = iter->toList();

            int eventCode = nestedList.first().toInt();
            if (eventCode == newMessage)
                ++count;
            else if (eventCode == messageWasRead
                     && (nestedList.at(2).toInt() & messageWasReadMask))
                --count;
        }

        return count;
    }
}

void ApiVK::post(QString message, QStringList attachments, int friendsOnly, int *errorCode) {
        // создает пост на стену со всеми параметрами
        // при возникновении ошибки выходим, присваивая errorCode её значение
    if (!m_auth.isAuthorised()) {
        if (errorCode) *errorCode = DidntAuthorised;
        return;
    }

    if (attachments.isEmpty()) {
        m_directApi.wall_post(message, "", friendsOnly);
    } else {
        m_postData.message = message;
        m_postData.friendsOnly = friendsOnly;

        connect(&m_uploader, SIGNAL(uploadFinished()), SLOT(postWithAttachments()));
        m_uploader.uploadFiles(attachments);
    }
}

void ApiVK::postWithAttachments() {
    QStringList attachments = m_uploader.getUploadedFilesList();
    QStringList words = m_postData.message.split(' ', QString::SkipEmptyParts);
#ifdef WIN_OLD_COMPILER
    foreach (const QString &word, words) {
#else
    for (const QString &word : words) {
#endif
        if (word.startsWith("http://") || word.startsWith("https://")) {
            attachments.append(word);
            break;
        }
    }

    m_directApi.wall_post(m_postData.message, attachments.join(","), m_postData.friendsOnly);
}

int ApiVK::postResult() {
        // возвращает результат функции post()
        // при возникновении какой-то ошибки возвращает её код, иначе 0
    if (!m_auth.isAuthorised()) {
        return DidntAuthorised;
    }

    QJson::Parser parser;
    bool ok;

    QVariantMap returnedData = parser.parse(m_returnedData, &ok).toMap();
    Q_ASSERT_X(ok, "Post result data analysing", "parser returned error");
    if (Q_UNLIKELY(!ok)) {
        qWarning() << tr("Post result data analysing: parser returned an error. Couldn't get post result.");
        return AnalysisError;
    }

    if (returnedData.contains("response")) {
        return NoError;
    } else if (returnedData.contains("error")) {
        QVariantMap errorMap = returnedData.value("error").toMap();

        m_serverErrorCode = errorMap.value("error").toString().toInt();
        m_serverErrorDescription = errorMap.value("error_msg").toString();

        return ServerError;
    } else {
        return AnalysisError;
    }
}
