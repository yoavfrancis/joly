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

#include "apivk_filesuploader.h"
#include "ostools_userfilesinterface.h"
#include <QVariant>
#include <QUrl>
#include <QtNetwork>
#include <QPixmap>
#include <QLabel>
#include <QJsonDocument>

ApiVK_FilesUploader::ApiVK_FilesUploader(QObject *parent) :
    QObject(parent), m_currFile(0) {

}

/////////////////////////////////upload files///////////////////////////////////
void ApiVK_FilesUploader::uploadFiles(const QStringList &files) {
    m_files = files;

    if (m_files.isEmpty()) {
        emit uploadFinished();
        return;
    }

    m_currFile = 0;
    uploadCurrFile();
}

void ApiVK_FilesUploader::uploadCurrFile() {
    using OSTools::UserFilesInterface;
    switch (UserFilesInterface::getFileKind(m_files.at(m_currFile))) {
        case UserFilesInterface::FileKind::image:
            uploadCurrPhoto();
            break;
        default:
            Q_ASSERT(false);
    }
}

void ApiVK_FilesUploader::uploadNextFile() {
    ++m_currFile;

    if (m_currFile == uint(m_files.length()))
        emit uploadFinished();
    else
        uploadCurrFile();
}

/////////////////////////////////upload photos///////////////////////////////////
void ApiVK_FilesUploader::uploadCurrPhoto() {
    connect(&m_directApi, SIGNAL(requestFinished(QByteArray)), SLOT(processWallUploadServer(QByteArray)));
    connect(&m_directApi, SIGNAL(requestFailed(int,QString)), SLOT(photoUploadingFailed(int,QString)));
    m_directApi.photos_getWallUploadServer();
}

// 1st stage
void ApiVK_FilesUploader::processWallUploadServer(const QByteArray &response) {
//    disconnect(&m_directApi, SIGNAL(requestFinished(QByteArray)), SLOT(processWallUploadServer(QByteArray)));
//    disconnect(&m_directApi, SIGNAL(requestFailed(int,QString)), SLOT(photoUploadingFailed(int,QString)));
    m_directApi.disconnect(this);

    QJsonParseError parseError;

    QVariant json = QJsonDocument::fromJson(response, &parseError).toVariant();
    if (Q_UNLIKELY(parseError.error)) {
        qWarning() << tr("Can't parse JSON data:") << response
                   << tr(". Parser returned an error:") << parseError.errorString();
        uploadNextFile();
        return;
    }
    Q_ASSERT_X(!parseError.error, "Returned data after uploading photo analysing", "parser returned error");

    QVariantMap jsonMap = json.toMap();

    if (jsonMap.contains("error")) {
        QVariantMap errorMap = jsonMap.value("error").toMap();

        qWarning() << "ApiVK::FilesUploader: server returned error" << errorMap.value("error").toString().toInt()
                   << "with description" << errorMap.value("error_msg").toString()
                   << "in method photos.getWallUploadServer";

        Q_ASSERT(false);
        uploadNextFile();
        return;
    }

    // generating boundary
    qsrand(QTime::currentTime().msec());
    QByteArray boundary = QString("-----------------" + QString::number(qrand())).toLatin1();
    QByteArray separateBoundary = QString("--" + boundary + "\r\n").toLatin1();
    QByteArray endBoundary = QString("--" + boundary + "--" + "\r\n").toLatin1();

    // getting mime type for image
    QString fileSuffix = QFileInfo(m_files.at(m_currFile)).suffix();
    QString mimeType;
    if (fileSuffix == "jpg" || fileSuffix == "jpeg" || fileSuffix == "jpe")
        mimeType = "image/jpeg";
    else
        mimeType = "image/" + fileSuffix;

//    qDebug() << mimeType;

    QString uploadServer = jsonMap.value("response").toMap().value("upload_url").toString();

    // creating request
    QNetworkRequest request(uploadServer);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + boundary);

    // creating request body
    QByteArray data;
    data.append(separateBoundary);
    data.append("Content-Disposition: form-data; name=\"photo\"; filename=\"" + QFileInfo(m_files.at(m_currFile)).fileName() + "\"\r\n");
    data.append(QString("Content-Type: " + mimeType + "\r\n").toLatin1());
    data.append("Content-Transfer-Encoding: binary\r\n");
    data.append("\r\n");

    QPixmap pixmap(m_files.at(m_currFile));
    QByteArray pixmapData;
    QBuffer buffer(&pixmapData);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer);

    QFile file(m_files.at(m_currFile));
    qDebug() << file.open(QIODevice::ReadOnly);
    QByteArray fileContent = file.readAll();

    data.append(fileContent);
    data.append("\r\n");
    data.append(endBoundary);

//    qDebug() << data;

//    QHttpPart imagePart;
//    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, mimeType);
//    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
//    QFile *file = new QFile(m_files.at(m_currFile));
//    file->open(QIODevice::ReadOnly);
//    imagePart.setBodyDevice(file);

//    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
//    multiPart->append(imagePart);

    request.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.length()).toLatin1());

    connect(&m_directApi, SIGNAL(requestFinished(QByteArray)), SLOT(saveWallPhoto(QByteArray)));
    connect(&m_directApi, SIGNAL(requestFailed(int,QString)), SLOT(photoUploadingFailed(int,QString)));
    m_directApi.photos_postPhotoToServer(request, data);
}

void ApiVK_FilesUploader::saveWallPhoto(const QByteArray &response) {
//    disconnect(&m_directApi, SIGNAL(requestFinished(QByteArray)), SLOT(processWallUploadServer(QByteArray)));
//    disconnect(&m_directApi, SIGNAL(requestFailed(int,QString)), SLOT(photoUploadingFailed(int,QString)));
    m_directApi.disconnect(this);

    QJsonParseError parseError;

    QVariant json = QJsonDocument::fromJson(response, &parseError).toVariant();
    if (Q_UNLIKELY(parseError.error)) {
        qWarning() << tr("Can't parse JSON data:") << response
                   << tr(". Parser returned an error:") << parseError.errorString();
        uploadNextFile();
        return;
    }
    Q_ASSERT_X(!parseError.error, "Returned data after uploading photo analysing", "parser returned error");

    QVariantMap jsonMap = json.toMap();

    if (jsonMap.contains("error")) {
        QVariantMap errorMap = jsonMap.value("error").toMap();

        qWarning() << "ApiVK::FilesUploader: server returned error" << errorMap.value("error").toString().toInt()
                   << "with description" << errorMap.value("error_msg").toString()
                   << "after posting photo.";
        Q_ASSERT(false);
        uploadNextFile();
        return;
    }

    QString server = jsonMap.value("server").toString();
    QString photo = jsonMap.value("photo").toString();
    QString hash = jsonMap.value("hash").toString();

    connect(&m_directApi, SIGNAL(requestFinished(QByteArray)), SLOT(finishUploadingPhoto(QByteArray)));
    connect(&m_directApi, SIGNAL(requestFailed(int,QString)), SLOT(photoUploadingFailed(int,QString)));
    m_directApi.photos_saveWallPhoto(server, photo, hash);
}

void ApiVK_FilesUploader::finishUploadingPhoto(const QByteArray &response) {
//    disconnect(&m_directApi, SIGNAL(requestFinished(QByteArray)), SLOT(finishUploadingPhoto(QByteArray)));
//    disconnect(&m_directApi, SIGNAL(requestFailed(int,QString)), SLOT(photoUploadingFailed(int,QString)));
    m_directApi.disconnect(this);

    QJsonParseError parseError;

    QVariant json = QJsonDocument::fromJson(response, &parseError).toVariant();
    if (Q_UNLIKELY(parseError.error)) {
        qWarning() << tr("Can't parse JSON data:") << response
                   << tr(". Parser returned an error:") << parseError.errorString();
        uploadNextFile();
        return;
    }
    Q_ASSERT_X(!parseError.error, "Returned data after uploading photo analysing", "parser returned error");

    QVariantMap jsonMap= json.toMap();

    if (jsonMap.contains("error")) {
        QVariantMap errorMap = jsonMap.value("error").toMap();

        qWarning() << "ApiVK::FilesUploader: server returned error" << errorMap.value("error").toString().toInt()
                   << "with description" << errorMap.value("error_msg").toString()
                   << "after saveWallPhoto.";
        Q_ASSERT(false);

        uploadNextFile();
        return;
    }

    QString photoId = jsonMap.value("id").toString();
    m_uploadedFiles.append(photoId);

    uploadNextFile();
}

void ApiVK_FilesUploader::photoUploadingFailed(int errorCode, QString errorDescription) {
    qWarning() << "Photo uploading error:" << errorCode << errorDescription;
    Q_ASSERT(false);
    uploadNextFile();
}
