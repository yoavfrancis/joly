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

#ifndef API_VK_H
#define API_VK_H

#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QtNetwork/QNetworkCookieJar>
#include <QPointer>
#include "apivkauth.h"
#include "apivkdirect.h"
#include "apivkpermissions.h"
#include "apivk_filesuploader.h"

class QWebView;
class QString;
class QNetworkReply;
class QXmlInputSource;
class QTimer;
class QNetworkCookie;


/**
 * @brief The ApiVK class is the interface for VK API.
 */
class ApiVK : public QObject
{
    Q_OBJECT
public:
    explicit ApiVK(QObject *parent = 0);

    enum ErrorKind { NoError, DidntAuthorised, PermissionsAreNeeded, NetworkError, AnalysisError, ServerError, UknownError };

    inline bool isAuthorised() const {
        return m_auth.isAuthorised();
    }

    inline int getServerErrorCode() const {
        return m_serverErrorCode;
    }

    inline QString getServerErrorDescription() const {
        return m_serverErrorDescription;
    }

signals:
    void authorisationFailed(QString error, QString error_description);
    void authorisationSucceed();

    void requestFailed(int errorCode, QString errorDescription);
    void requestFinished();

public slots:
    inline void authorise() {
        m_auth.authorise();
    }

    inline void newAuthoriseRequest() {
        m_auth.newAuthoriseRequest();
    }

    void getUnreadMessagesVariationRequest(int *errorCode = 0);
    int  getUnreadMessagesVariation(int *errorCode = 0);

    void post(QString message = QString(), QStringList attachments = QStringList(), int friendsOnly = -1, int *errorCode = 0);
    int  postResult();

private slots:
    inline void handleRequestFinish(QByteArray data) {
        m_returnedData = data;
        emit requestFinished();
    }

    void special_longPollServerDataReturned(QNetworkReply *reply);

    void postWithAttachments();

private:
    QByteArray m_returnedData;

    ApiVKDirect m_directApi;
    ApiVKAuth m_auth;

    ApiVK_FilesUploader m_uploader;

    int m_serverErrorCode;
    QString m_serverErrorDescription;

    struct LongPollServerData {
        LongPollServerData() : initialized(false) { }
        QString key;
        QString serverAddress;
        QString ts;
        bool initialized;
    } m_lpsData;

    struct anonymous {
        QString message;
        int friendsOnly;
    } m_postData;
};

#endif // API_VK_H
