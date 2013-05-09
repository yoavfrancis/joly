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

#ifndef GEOREVERSE_H
#define GEOREVERSE_H

#include <QWidget>

namespace Ui {
    class GeoReverse;
}

class OAuthTwitter;
class QTweetPlace;

class GeoReverse : public QWidget
{
    Q_OBJECT

public:
    explicit GeoReverse(QWidget *parent = 0);
    ~GeoReverse();

protected:
    void changeEvent(QEvent *e);

private slots:
    void onSearchPushButtonClicked();
    void reverseGeoFinished(const QList<QTweetPlace>& places);

private:
    Ui::GeoReverse *ui;
    OAuthTwitter *m_oauthTwitter;

};

#endif // GEOREVERSE_H
