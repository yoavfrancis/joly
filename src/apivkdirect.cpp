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

#include "apivkdirect.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QtNetwork>

ApiVKDirect::ApiVKDirect(QString access_token, QObject *parent) :
    QObject(parent), m_accessToken(access_token)
{ }

void ApiVKDirect::messages_get(int filters, int out, int offset, int count, int preview_length, int time_offset) {
        // метод для прямой работы с методом API Вконтакте messages.get
    QUrl url("https://api.vk.com/method/messages.get");
    QUrlQuery query;
    if (out != -1)
        query.addQueryItem("out", QString::number(out));
    if (offset != -1)
        query.addQueryItem("offset", QString::number(offset));
    if (count != -1)
        query.addQueryItem("count", QString::number(count));
    if (filters != -1)
        query.addQueryItem("filters", QString::number(filters));
    if (preview_length != -1)
        query.addQueryItem("preview_length", QString::number(preview_length));
    if (time_offset != -1)
        query.addQueryItem("time_offset", QString::number(time_offset));
    query.addQueryItem("access_token", m_accessToken);

    url.setQuery(query);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(url));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processRequest(QNetworkReply*)));
}

void ApiVKDirect::wall_post(QString message, QString attachments, int friends_only, int owner_id, QString services, int from_group, int n_signed) {
        // метод для прямой работы с методом API Вконтакте wall.post
    QUrl url("https://api.vk.com/method/wall.post");
    QUrlQuery query;
    if (owner_id != -1)
        query.addQueryItem("owner_id", QString::number(owner_id));
    if (message != "")
        query.addQueryItem("message", message);
    if (attachments != "")
        query.addQueryItem("count", attachments);
    if (services != "")
        query.addQueryItem("services", services);
    if (from_group != -1)
        query.addQueryItem("from_group", QString::number(from_group));
    if (n_signed != -1)
        query.addQueryItem("signed", QString::number(n_signed));
    if (friends_only != -1)
        query.addQueryItem("friends_only", QString::number(friends_only));
    query.addQueryItem("access_token", m_accessToken);

    url.setQuery(query);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(url));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processRequest(QNetworkReply*)));
}

void ApiVKDirect::photos_getWallUploadServer() {
    QUrl url("https://api.vk.com/method/photos.getWallUploadServer");
    QUrlQuery query;
    query.addQueryItem("access_token", m_accessToken);
    url.setQuery(query);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(url));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processRequest(QNetworkReply*)));
}

void ApiVKDirect::photos_postPhotoToServer(const QNetworkRequest &request, const QByteArray &data) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->post(request, data);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processRequest(QNetworkReply*)));
}

void ApiVKDirect::photos_saveWallPhoto(const QString &server, const QString &photo, const QString &hash) {
    QUrl url("https://api.vk.com/method/photos.saveWallPhoto");
    QUrlQuery query;
    query.addQueryItem("server", server);
    query.addQueryItem("photo", photo);
    query.addQueryItem("hash", hash);
    query.addQueryItem("access_token", m_accessToken);
    url.setQuery(query);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(url));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processRequest(QNetworkReply*)));
}

void ApiVKDirect::askLongPollServer(QString serverAddress, QString key, QString ts, int wait, int mode) {
    QUrl url(QString("http://%1").arg(serverAddress));
    QUrlQuery query;
    query.addQueryItem("act", "a_check");
    query.addQueryItem("key", key);
    query.addQueryItem("ts", ts);
    query.addQueryItem("wait", QString::number(wait));
    query.addQueryItem("mode", QString::number(mode));
    url.setQuery(query);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(url));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(processRequest(QNetworkReply*)));
}

void ApiVKDirect::processRequest(QNetworkReply *reply) {
        // вызывается по окончанию запроса к сереру из методов прямой работы с API Вконтакте
        // сохраняет ответ сервера в виде XML в строку и генерирует сигнал requestFinished(QString) с содержанием XML
    if (reply->error()) {
        emit requestFailed(reply->error(), reply->errorString());
        return;
    }

    m_returnedData = reply->readAll();
    reply->deleteLater();

    emit requestFinished(m_returnedData);
}
