/* Copyright 2012 Antonie Jovanoski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Contact e-mail: Antonie Jovanoski <minimoog77_at_gmail.com>
 */

#include "qtweetstatusretweetedby.h"
#include <QtDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include "qtweetuser.h"
#include "qtweetconvert.h"
#include <QJsonDocument>
#include <QJsonArray>

QTweetStatusRetweetedBy::QTweetStatusRetweetedBy(QObject *parent) :
    QTweetNetBase(parent),
    m_tweetid(0),
    m_count(0),
    m_page(0)
{
}

QTweetStatusRetweetedBy::QTweetStatusRetweetedBy(OAuthTwitter *oauthTwitter, QObject *parent) :
    QTweetNetBase(oauthTwitter, parent),
    m_tweetid(0),
    m_count(0),
    m_page(0)
{
}

void QTweetStatusRetweetedBy::fetch(qint64 tweetid, int count, int page)
{
    if (!isAuthenticationEnabled()) {
        qCritical("Needs authentication to be enabled");
        return;
    }

    QString urlString = QString("http://api.twitter.com/1/statuses/%1/retweeted_by.json").arg(tweetid);
    QUrl url(urlString);
    QUrlQuery urlQuery;

    if (count != 0)
        urlQuery.addQueryItem("count", QString::number(count));

    if (page != 0)
        urlQuery.addQueryItem("page", QString::number(page));

    url.setQuery(urlQuery);

    QNetworkRequest req(url);

    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::GET);
    req.setRawHeader(AUTH_HEADER, oauthHeader);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->get(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
}

void QTweetStatusRetweetedBy::get()
{
    fetch(m_tweetid, m_count, m_page);
}

void QTweetStatusRetweetedBy::parseJsonFinished(const QJsonDocument &jsonDoc)
{
    if (jsonDoc.isArray()) {
        QList<QTweetUser> users = QTweetConvert::jsonArrayToUserInfoList(jsonDoc.array());

        emit parsedUsers(users);
    }
}
