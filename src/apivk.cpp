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
#include <QVariant>
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include "ostools.h"
#include "consts.h"
#include "apivkdirect.h"
#include "apivkauth.h"

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
        QUrlQuery query;
        query.addQueryItem("access_token", m_auth.getAccessToken());
        url.setQuery(query);

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

    QJsonParseError parseError;

    QVariant json = QJsonDocument::fromJson(content, &parseError).toVariant();
    if (Q_UNLIKELY(parseError.error)) {
        qWarning() << tr("Can't parse JSON data:") << content
                   << tr(". Parser returned an error:") << parseError.errorString();
        return;
    }
    Q_ASSERT_X(!parseError.error, "LongPollServer data analysing", "parser returned error");

    if (json.toMap().contains("response")) {
        QVariantMap nestedData = json.toMap().value("response").toMap();
        m_lpsData.key = nestedData.value("key").toString();
        m_lpsData.serverAddress = nestedData.value("server").toString().replace(QString("\\/"), QChar('/'));
        m_lpsData.ts = nestedData.value("ts").toString();
        m_lpsData.initialized = true;
    }
}

int ApiVK::getUnreadMessagesVariation(int *errorCode) {
        // возвращает результат выполнения функции getUnreadMessagesRequest()
        // при возникновении ошибки возвращает -1 и код ошибки в errorCode (если передана)
    if (!m_auth.isAuthorised()) {
        if (errorCode) *errorCode = DidntAuthorised;
        return -1;
    }

    QJsonParseError parseError;

    QVariant json = QJsonDocument::fromJson(m_returnedData, &parseError).toVariant();
    if (Q_UNLIKELY(parseError.error)) {
        qWarning() << tr("Can't parse JSON data:") << m_returnedData
                   << tr(". Parser returned an error:") << parseError.errorString();

        if (errorCode) *errorCode = AnalysisError;
        return -1;
    }
    Q_ASSERT_X(!parseError.error, "Messages data analysing", "parser returned error");

    QVariantMap jsonMap = json.toMap();

    // if it's result of messages.get
    if (jsonMap.contains("response")) {
        return jsonMap.value("response").toList().first().toInt();
    }
    else {
        m_lpsData.ts = jsonMap.value("ts").toString();
        QVariantList updates = jsonMap.value("updates").toList();

        int count = 0;
        const short int newMessage = 4;
        const short int messageWasRead = 3;
        const short int messageWasReadMask = 1;

        /* FIXME: the new VK API version returns "message was read" mask not only when app's user
         * reads the message, but also when his interlocutor does so.
         */
        for (auto iter = updates.constBegin(); iter != updates.constEnd(); ++iter) {
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
    forc11 (const QString &word, words) {
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

    QJsonParseError parseError;

    QVariant json = QJsonDocument::fromJson(m_returnedData, &parseError).toVariant();
    if (Q_UNLIKELY(parseError.error)) {
        qWarning() << tr("Can't parse JSON data:") << m_returnedData
                   << tr(". Parser returned an error:") << parseError.errorString();
        return AnalysisError;
    }
    Q_ASSERT_X(!parseError.error, "Post result data analysing", "parser returned error");

    QVariantMap jsonMap = json.toMap();

    if (jsonMap.contains("response")) {
        return NoError;
    } else if (jsonMap.contains("error")) {
        QVariantMap errorMap = jsonMap.value("error").toMap();

        m_serverErrorCode = errorMap.value("error").toString().toInt();
        m_serverErrorDescription = errorMap.value("error_msg").toString();

        return ServerError;
    } else {
        return AnalysisError;
    }
}
