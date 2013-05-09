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

#ifndef QTWEETGEOPLACEID_H
#define QTWEETGEOPLACEID_H

#include "qtweetnetbase.h"

class QTweetPlace;

/**
 *  Fetches all the information about a known place
 */
class QTWEETLIBSHARED_EXPORT QTweetGeoPlaceID : public QTweetNetBase
{
    Q_OBJECT
public:
    QTweetGeoPlaceID(QObject *parent = 0);
    QTweetGeoPlaceID(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    void get(const QString& placeid);

signals:
    /** Emits the place */
    void parsedPlace(const QTweetPlace& place);

protected slots:
    void parseJsonFinished(const QJsonDocument &jsonDoc);
};

#endif // QTWEETGEOPLACEID_H
