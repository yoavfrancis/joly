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

#include "apitwiauth.h"
#include <QtCore>
#include <string>
#include "apitwiauth_twitterpinwidget.h"
#include <QNetworkAccessManager>

#include "QtTweetLib/qtweetstatus.h"
#include "QtTweetLib/qtweetstatusupdate.h"
#include "QtTweetLib/qtweetaccountverifycredentials.h"

#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

// TODO: remove is unnecessary
//const QString ApiTwiAuth::m_consumerKey = "uSH5FekxEhWTdl84WwpUTw";
//const QString ApiTwiAuth::m_consumerSecret = "wKSynlJaNUawWDYDaqpy7efLxWe4Wr00iKUA1hu4SrI";

bool ApiTwiAuth::m_needsUserAccountData = true;
bool ApiTwiAuth::m_authorised = false;
bool ApiTwiAuth::m_inAuthorisationProcess = false;

QString ApiTwiAuth::m_oAuthToken;
QString ApiTwiAuth::m_oAuthTokenSecret;

ApiTwiAuth::ApiTwiAuth(OAuthTwitter *oAuthTwitter, QObject *parent) :
    QObject(parent), m_oAuthTwitter(oAuthTwitter)
{
    readSettings();
}

void ApiTwiAuth::authorise() {
    startAuthorisation();
}

/////////////////////////Auth process/////////////////////////
void ApiTwiAuth::startAuthorisation() {
    m_inAuthorisationProcess = true;
    m_oAuthTwitter->setNetworkAccessManager(new QNetworkAccessManager(this));
//    m_oAuthTwitter->setConsumerKey(m_consumerKey.toLatin1());
//    m_oAuthTwitter->setConsumerSecret(m_consumerSecret.toLatin1());

    if (m_oAuthToken.isEmpty()) {
        newAuthoriseRequest();
    } else {
        m_oAuthTwitter->setOAuthToken(m_oAuthToken.toLatin1());
        m_oAuthTwitter->setOAuthTokenSecret(m_oAuthTokenSecret.toLatin1());
        completeAuth();
    }
}

// It makes new authorisation request using pin system
void ApiTwiAuth::newAuthoriseRequest() {
    m_oAuthTwitter->clearTokens();
    m_oAuthToken = "";
    m_oAuthTokenSecret = "";
    writeSettings();

    TwitterPinWidget *pinWidget = new TwitterPinWidget;
    pinWidget->show();
    connect(pinWidget, SIGNAL(openLinkAsked()), SLOT(openPinLink()));
    connect(pinWidget, SIGNAL(pinEntered(QString)), SLOT(continueWithPin(QString)));
    connect(pinWidget, SIGNAL(pinCancelled()), SIGNAL(authorisationCancelled()));
}

void ApiTwiAuth::openPinLink() {
    connect(m_oAuthTwitter, SIGNAL(authorizePinFinished()), SLOT(completeAuth()));
    // The strange error is here: pin authorization link often opens without any token passed in the url.
    m_oAuthTwitter->authorizePin();
}

// It finishes pin authorisation
void ApiTwiAuth::continueWithPin(QString pin) {
    m_oAuthTwitter->requestAccessToken(pin);

    m_oAuthToken = m_oAuthTwitter->oauthToken();
    m_oAuthTokenSecret = m_oAuthTwitter->oauthTokenSecret();
}

// It checks whether auth was succeed and emits correspinding signals
void ApiTwiAuth::completeAuth() {
    if (m_oAuthToken.isEmpty()) m_oAuthToken = m_oAuthTwitter->oauthToken();
    if (m_oAuthTokenSecret.isEmpty()) m_oAuthTokenSecret = m_oAuthTwitter->oauthTokenSecret();

    setIsAuthorised(true);
    writeSettings();
    m_inAuthorisationProcess = false;
}
/////////////////////////End of auth process/////////////////////////

void ApiTwiAuth::readSettings() {
    QSettings settings;
    settings.beginGroup("ApiTwitter");
    m_oAuthToken = settings.value("tokenKey").toString();
    m_oAuthTokenSecret = settings.value("tokenSecret").toString();
    settings.endGroup();
}

void ApiTwiAuth::writeSettings() {
    QSettings settings;
    settings.beginGroup("ApiTwitter");
    settings.setValue("tokenKey", m_oAuthToken);
    settings.setValue("tokenSecret", m_oAuthTokenSecret);
    settings.endGroup();
}
