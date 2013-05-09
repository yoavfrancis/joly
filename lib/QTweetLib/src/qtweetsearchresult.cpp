/* Copyright 2010 Antonie Jovanoski
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

#include "qtweetsearchresult.h"
#include <QSharedData>
#include <QDateTime>
//#include "qtweetuser.h"

class QTweetSearchResultData : public QSharedData {
public:
    QDateTime createdAt;
    QString fromUser;
    //qint64 fromUserId;    // USELESS. It's not same as general twitter user id
    qint64 id;
    QString lang;
    //metadata ### TODO
    //places ### TODO
    QString profileImageUrl;
    QString source;
    QString text;
    QString toUser;
    //qint64 toUserId;      // USELESS. It's not same general twitter user id
};

QTweetSearchResult::QTweetSearchResult() : data(new QTweetSearchResultData)
{
}

QTweetSearchResult::QTweetSearchResult(const QTweetSearchResult &rhs) : data(rhs.data)
{
}

QTweetSearchResult &QTweetSearchResult::operator=(const QTweetSearchResult &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QTweetSearchResult::~QTweetSearchResult()
{
}

void QTweetSearchResult::setCreatedAt(const QDateTime &dateTime)
{
    data->createdAt = dateTime;
}

// Oh, not again. ANOTHER datetime format from twitter.
//Mon, 04 Oct 2010 12:51:42 +0000

void QTweetSearchResult::setCreatedAt(const QString &twitterDate)
{
    QString dateString = twitterDate.left(3) + ' ' + twitterDate.mid(8, 3) + ' ' +
                         twitterDate.mid(5, 2) + ' ' + twitterDate.mid(12, 4);
    QString timeString = twitterDate.mid(17, 8);

    QDate date = QDate::fromString(dateString);
    QTime time = QTime::fromString(timeString);

    if (date.isValid() && time.isValid())
        data->createdAt = QDateTime(date, time, Qt::UTC);
    else
        data->createdAt = QDateTime();
}

QDateTime QTweetSearchResult::createdAt() const
{
    return data->createdAt;
}

void QTweetSearchResult::setFromUser(const QString &screenName)
{
    data->fromUser = screenName;
}

QString QTweetSearchResult::fromUser() const
{
    return data->fromUser;
}

void QTweetSearchResult::setId(qint64 id)
{
    data->id = id;
}

qint64 QTweetSearchResult::id() const
{
    return data->id;
}

void QTweetSearchResult::setLang(const QString &lang)
{
    data->lang = lang;
}

QString QTweetSearchResult::lang() const
{
    return data->lang;
}

void QTweetSearchResult::setProfileImageUrl(const QString &url)
{
    data->profileImageUrl = url;
}

QString QTweetSearchResult::profileImageUrl() const
{
    return data->profileImageUrl;
}

void QTweetSearchResult::setSource(const QString &source)
{
    data->source = source;
}

QString QTweetSearchResult::source() const
{
    return data->source;
}

void QTweetSearchResult::setText(const QString &text)
{
    data->text = text;
}

QString QTweetSearchResult::text() const
{
    return data->text;
}

void QTweetSearchResult::setToUser(const QString &screenName)
{
    data->toUser = screenName;
}

QString QTweetSearchResult::toUser() const
{
    return data->toUser;
}



