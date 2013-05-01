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

#ifndef APIVKDIRECT_H
#define APIVKDIRECT_H

#include <QObject>

class QHttpMultiPart;
class QNetworkReply;
class QNetworkRequest;

class ApiVKDirect : public QObject
{
    Q_OBJECT
public:
    explicit ApiVKDirect(QString access_token = "", QObject *parent = 0);

    inline QString getAccessToken() {
        return m_accessToken;
    }

    inline QString getReturnedData() {
        return m_returnedData;
    }
    
signals:
    void requestFailed(int errorCode, QString errorDescription);
    void requestFinished(QByteArray data);
//    void specialRequestFinished(QString data);
    
public slots:
    void wall_post(QString  message     = "",
                   QString  attachments = "",
                   int      friends_only = -1,
                   int      owner_id    = -1,
                   QString  services    = "",
                   int      from_group  = -1,
                   int      n_signed    = -1);

    void messages_get(int   filters     = -1,
                      int   out         = -1,
                      int   offset      = -1,
                      int   count       = -1,
                      int   preview_length = -1,
                      int   time_offset = -1);

    void askLongPollServer(QString serverAddress,
                           QString key,
                           QString ts,
                           int     wait = 25,
                           int     mode = 0);

    void photos_getWallUploadServer();
    void photos_postPhotoToServer(const QNetworkRequest &request, const QByteArray &data);
    void photos_saveWallPhoto(const QString &server, const QString &photo, const QString &hash);

    inline void setAccessToken(const QString& token) {
        m_accessToken = token;
    }

protected slots:
    void processRequest(QNetworkReply *reply);
//    void processSpecialRequest(QNetworkReply *reply);

private:
    QString m_accessToken;

    QByteArray m_returnedData;

//    QString m_callerUID;
};

#endif // APIVKDIRECT_H
