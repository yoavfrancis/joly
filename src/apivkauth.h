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

#ifndef APIVKAUTH_H
#define APIVKAUTH_H

#include <QObject>
#include <QPointer>
#include "apivkpermissions.h"

class QWebView;
class QNetworkCookie;
class QNetworkCookieJar;
class QTimer;
class QUrl;

class ApiVKAuth : public QObject
{
    Q_OBJECT
public:
    explicit ApiVKAuth(QObject *parent = 0);

    inline QString getAccessToken() {
        return m_accessToken;
    }

    inline int getExpiresIn() {
        return m_expiresIn;
    }

    inline bool isAuthorised() const {
        return m_authorised;
    }

    inline bool isInAuthProcess() const {
        return m_inAuthorisationProcess;
    }
    
signals:
    void authorisationFailed(QString error, QString errorDescription);
    void authorisationSucceed(QString access_token);
    
public slots:
    void authorise();
    void newAuthoriseRequest();

protected:
    void readSettings();
    void writeSetting();

protected slots:
    void processUrl(QUrl url);

    void waitForEndOfAuth();

    void finishAuthorisation(bool authResult);

private:
    static const QString m_appId;
    static QString m_accessToken;
    static qint32 m_expiresIn;

    QPointer<QWebView> m_loginPage;
    QPointer<QTimer> m_authorisationTimer;

    static bool m_authorised;
    static bool m_inAuthorisationProcess;

    static QString m_lastError;
    static QString m_lastErrorDescription;

    ApiVKPermissions m_permissions;
};

#endif // APIVKAUTH_H
