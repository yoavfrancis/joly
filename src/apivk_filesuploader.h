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

#ifndef APIVK_FILESUPLOADER_H
#define APIVK_FILESUPLOADER_H

#include <QObject>
#include <QStringList>
#include "apivkdirect.h"
#include <QNetworkAccessManager>

class ApiVK_FilesUploader : public QObject
{
    Q_OBJECT
public:
    explicit ApiVK_FilesUploader(QObject *parent = 0);

    void uploadFiles (const QStringList &files);
    inline QStringList getUploadedFilesList() const {
        return m_uploadedFiles;
    }
    
signals:
    void uploadFinished();

public slots:
    inline void setAccessToken(const QString &accessToken) {
        m_directApi.setAccessToken(accessToken);
    }
    
protected:
    void uploadCurrFile();
    void uploadCurrPhoto();

    void uploadNextFile();

protected slots:
    // Photos
    void processWallUploadServer(const QByteArray &response);
    void saveWallPhoto(const QByteArray &response);
    void finishUploadingPhoto(const QByteArray &response);

    void photoUploadingFailed(int errorCode, QString errorDescription);

private:
    QStringList m_files;
    QStringList m_uploadedFiles;
    uint m_currFile;
    ApiVKDirect m_directApi;

    // Photos
    QString m_wallUploadServer;
};

#endif // APIVK_FILESUPLOADER_H
