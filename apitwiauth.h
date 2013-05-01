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

#ifndef APITWIAUTH_H
#define APITWIAUTH_H

#include <QObject>
#include <QtTweetLib/oauthtwitter.h>
#include <QPointer>

class ApiTwiAuth : public QObject
{
    Q_OBJECT

public:
    explicit ApiTwiAuth(OAuthTwitter *oAuthTwitter, QObject *parent = 0);

    inline bool isAuthorised() const {
        return m_authorised;
    }

    inline bool isInAuthProcess() const {
        return m_inAuthorisationProcess;
    }
    
signals:
    void authorisationFailed(/*QString error, QString errorDescription*/);
    void authorisationCancelled();
    void authorisationSucceed();
    
public slots:
    void authorise();
    void newAuthoriseRequest();

protected:
    void readSettings();
    void writeSettings();

protected slots:
    void startAuthorisation();
    void openPinLink();
    void continueWithPin(QString pin);
    void completeAuth();

    // Sets auth status ans emits suitable signal
    inline void setIsAuthorised(bool status) {
        m_authorised = status;
        if (status)
            emit authorisationSucceed();
        else
            emit authorisationFailed();
    }

private:
    static const QString m_consumerKey;
    static const QString m_consumerSecret;
    static QString m_oAuthToken;
    static QString m_oAuthTokenSecret;

    static bool m_needsUserAccountData;
    static bool m_authorised;
    static bool m_inAuthorisationProcess;

    OAuthTwitter *m_oAuthTwitter;
};

#endif // APITWIAUTH_H
