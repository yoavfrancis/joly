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

#include "apivkauth.h"
#include <QtWidgets>
#include <QWebView>
#include <QTimer>
#include <QDebug>
#include <QNetworkCookieJar>
#include <QNetworkRequest>
#include <QWebFrame>
#include <QJsonDocument>
#include "ostools.h"
#include "consts.h"

    // defining static class members

bool ApiVKAuth::m_authorised = false;
bool ApiVKAuth::m_inAuthorisationProcess = false;
const QString ApiVKAuth::m_appId = "2783286";
QString ApiVKAuth::m_accessToken = QString();
int ApiVKAuth::m_expiresIn = 0;
QString ApiVKAuth::m_lastError = "";
QString ApiVKAuth::m_lastErrorDescription = "";

    // defining class methods

ApiVKAuth::ApiVKAuth(QObject *parent) :
    QObject(parent), m_authorisationTimer(new QTimer(this)), m_permissions(ApiVKPermissions("wall,messages,photos,offline"))
{
    readSettings();
}

void ApiVKAuth::authorise() {
    if (m_accessToken.isEmpty())
        newAuthoriseRequest();
    else
        finishAuthorisation(true);
}

void ApiVKAuth::newAuthoriseRequest() {
    if (m_inAuthorisationProcess) {

        connect(m_authorisationTimer, SIGNAL(timeout()), this, SLOT(waitForEndOfAuth()));
        m_authorisationTimer->start(100);

    } else {

        m_inAuthorisationProcess = true;

        m_loginPage = new QWebView;
        m_loginPage->setWindowTitle(tr("Вход во ВКонтакте", "Window title of login page for VK Api. In English ВКонтакте must be VK."));

        QUrl url("https://oauth.vk.com/authorize");
        QUrlQuery query;
        query.addQueryItem("client_id", m_appId);
        query.addQueryItem("scope", m_permissions.toString());
        query.addQueryItem("redirect_uri","https://oauth.vk.com/blank.html");
        query.addQueryItem("display","page");
        query.addQueryItem("response_type","token");
        url.setQuery(query);

        m_loginPage->load(QNetworkRequest(url));
        connect(m_loginPage, SIGNAL(urlChanged(QUrl)), this, SLOT(processUrl(QUrl)));
    }
}

void ApiVKAuth::processUrl(QUrl url)
{
    if (url.host() == "oauth.vk.com" && ( url.path().startsWith("/oauth/authorize") || url.path().startsWith("/authorize") || url.path().startsWith("/error"))) {
        // Showing auth window
        m_loginPage->show();
        return;
    }

    if (url.toString().indexOf('?') == -1) {
        QString temp;

        temp = url.toString();
        temp[temp.indexOf('#')] = '?';
        url = temp;
    }

    if (QUrlQuery(url).hasQueryItem("err") || QUrlQuery(url).hasQueryItem("error")) {
        QByteArray content = m_loginPage->page()->mainFrame()->toPlainText().toLocal8Bit();

        QJsonParseError parseError;

        QVariant json = QJsonDocument::fromJson(content, &parseError).toVariant();
        if (Q_UNLIKELY(parseError.error)) {
            qWarning() << tr("Can't parse JSON data:") << content
                       << tr(". Parser returned an error:") << parseError.errorString();
        }

        QVariantMap jsonMap = json.toMap();
        m_lastError = jsonMap.value("error").toString();
        m_lastErrorDescription = jsonMap.value("error_description").toString();

        finishAuthorisation(false);

        return;
    }

    if (Q_UNLIKELY(!QUrlQuery(url).hasQueryItem("access_token"))) {
        qWarning() << "ApiVKAuth:" << "returned url have not query item 'access_token'."
                   << "Social functions for VK may not work.";
    }
    Q_ASSERT(QUrlQuery(url).hasQueryItem("access_token"));

    m_accessToken = QUrlQuery(url).queryItemValue("access_token");
    m_expiresIn = QUrlQuery(url).queryItemValue("expires_in").toInt();

    finishAuthorisation(true);
}

void ApiVKAuth::waitForEndOfAuth()
{
        // вызывается таймером из newAuthoriseRequest(), если в другом экземпляре класса в этот момент происходит авторизация
        // после окончания авторизации генерирует событие успешности или ошибки
    if (m_inAuthorisationProcess)
        return;

    m_authorisationTimer->stop();

    if (m_authorised)
        emit authorisationSucceed(m_accessToken);
    else
        emit authorisationFailed(m_lastError, m_lastErrorDescription);
}

void ApiVKAuth::finishAuthorisation(bool authResult) {
    m_authorised = authResult;
    m_inAuthorisationProcess = false;

    if (m_loginPage) {
        m_loginPage->deleteLater();
        m_loginPage = nullptr;
    }

    writeSetting();

    if (authResult)
       emit authorisationSucceed(m_accessToken);
    else
       emit authorisationFailed(m_lastError, m_lastErrorDescription);
}

void ApiVKAuth::readSettings() {
    QSettings settings;
    settings.beginGroup("ApiVK");
    m_accessToken = settings.value("accessToken").toString();
    settings.endGroup();
}

void ApiVKAuth::writeSetting() {
    QSettings settings;
    settings.beginGroup("ApiVK");
    settings.setValue("accessToken", m_accessToken);
    settings.endGroup();
}
