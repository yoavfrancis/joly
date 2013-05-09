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

#ifndef APITWI_H
#define APITWI_H

#include <QObject>
#include <QtTweetLib/oauthtwitter.h>
#include <QDebug>
#include "apitwiauth.h"
#include <QNetworkReply>
#include <QtTweetLib/qtweetnetbase.h>

/**
 * @brief The ApiTwi class is the interface for the Twitter API.
 */
class ApiTwi : public QObject
{
    Q_OBJECT
public:
    explicit ApiTwi(QObject *parent = 0);

    inline bool isAuthorised() const {
        return m_auth.isAuthorised();
    }

signals:
    void authorisationFailed();
    void authorisationSucceed();

    void requestFailed(QTweetNetBase::ErrorCode,QString);
    void requestFinished();

    void configurationIsReady(QVariantMap config);

public slots:
    /**
     * @brief Authorises an user.
     * For detailed documentation, look at ApiTwiAuth::authorise().
     */
    inline void authorise() {
        m_auth.authorise();
    }

    /**
     * @brief Force starts authorisation process.
     * For detailed documentation, look at ApiTwiAuth::authorise().
     */
    inline void newAuthoriseRequest() {
        m_auth.newAuthoriseRequest();
    }

    void post(QString message); ///< Performs status update.
    int  postResult() const;

    QVariantMap getConfiguration() const;

private slots:
    inline void handleRequestFinish(QNetworkReply* reply) {
        handleRequestFinish(reply->readAll());
    }

    inline void handleRequestFinish(QByteArray data) {
        m_lastRequestResult.returnedData = data;
        m_lastRequestResult.thereWasError = false;

        emit requestFinished();
    }

    inline void handleRequestError(QTweetNetBase::ErrorCode errorCode, QString errorString) {
        m_lastRequestResult.clear();
        m_lastRequestResult.thereWasError = true;
        m_lastRequestResult.errorCode = errorCode;

        emit requestFailed(errorCode, errorString);
    }

    void getConfigurationRequest();
    void saveConfiguration(QNetworkReply* reply);

private:
    static OAuthTwitter m_oAuthTwitter;
    mutable ApiTwiAuth m_auth;
    static QVariantMap m_configuration;

    struct _lastRequestResult {
        QByteArray returnedData;
        bool thereWasError;

        int errorCode;

        inline void clear() { returnedData.clear(); thereWasError = false; errorCode = 0; }
    } m_lastRequestResult;
};

#endif // APITWI_H
