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

#ifndef QTWEETHOMETIMELINE_H
#define QTWEETHOMETIMELINE_H

#include "qtweetnetbase.h"

/**
 *   Fetches user home timeline
 */
class QTWEETLIBSHARED_EXPORT QTweetHomeTimeline : public QTweetNetBase
{
    Q_OBJECT
    Q_PROPERTY(qint64 sinceID READ sinceID WRITE setSinceID)
    Q_PROPERTY(qint64 maxID READ maxID WRITE setMaxID)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_PROPERTY(bool trimUser READ isTrimUser WRITE setTrimUser)
    Q_PROPERTY(bool includeEntities READ isIncludeEntities WRITE setIncludeEntities)
    Q_PROPERTY(bool excludeReplies READ isExcludeReplies WRITE setExcludeReplies)
    Q_PROPERTY(bool contributorDetails READ isContributorsDetails WRITE setContributorsDetails)

public:
    QTweetHomeTimeline(QObject *parent = 0);
    QTweetHomeTimeline(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    void fetch(qint64 sinceid = 0,
               qint64 maxid = 0,
               int count = 0,
               bool trimUser = false,
               bool includeEntities = false,
               bool excludeReplies = false,
               bool contributorDetails = false);
    void get();

    void setSinceID(qint64 sinceid) { m_sinceid = sinceid; }
    qint64 sinceID() const { return m_sinceid; }

    void setMaxID(qint64 maxid) { m_maxid = maxid; }
    qint64 maxID() const { return m_maxid; }

    void setCount(int count) { m_count = count; }
    int count() const { return m_count; }

    void setTrimUser(bool trimUser) { m_trimUser = trimUser; }
    bool isTrimUser() const { return m_trimUser; }

    void setIncludeEntities(bool includeEntities) { m_includeEntities = includeEntities; }
    bool isIncludeEntities() const { return m_includeEntities; }

    void setExcludeReplies(bool excludeReplies) { m_excludeReplies = excludeReplies; }
    bool isExcludeReplies() const { return m_excludeReplies; }

    void setContributorsDetails(bool contributorsDetails) { m_contributorDetails = contributorsDetails; }
    bool isContributorsDetails() const { return m_contributorDetails; }

signals:
    /** Emits hometimeline status list */
    void parsedStatuses(const QList<QTweetStatus>& statuses);

protected slots:
    void parseJsonFinished(const QJsonDocument &jsonDoc);

private:
    // ### TODO: Use pimpl
    qint64 m_sinceid;
    qint64 m_maxid;
    int m_count;
    bool m_trimUser;
    bool m_includeEntities;
    bool m_excludeReplies;
    bool m_contributorDetails;
};

#endif // QTWEETHOMETIMELINE_H
