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

#ifndef OSTOOLS_H
#define OSTOOLS_H

#include <QMap>
#include <QStringList>
#include <QString>
#include <QChar>
#include <QRegExp>
#include <QDesktopServices>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QtDebug>

namespace OSTools
{
     inline bool notifySend (const QString &text) { // only Linux
            // отправляет сообщение с помощью linux-утилиты notify-send
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        QProcess pr;
        return pr.startDetached(QString("notify-send"), QStringList() << text);
    }


    inline void file (const QString &path) {
            // открывает файл с помощью QDesktopServices::openUrl
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
#ifdef Q_OS_WIN
        QString scheme = "file:///";
#else
        QString scheme = "file://";
#endif
        if (!path.startsWith(scheme, Qt::CaseInsensitive))
            QDesktopServices::openUrl(QUrl(/*'"' + */scheme + path/* + '"'*/));
        else
            QDesktopServices::openUrl(QUrl(/*'"' + */path/* + '"'*/));
    }

    inline void file (const QUrl &path) {
            // открывает файл с помощью QDesktopServices::openUrl
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
#ifdef Q_OS_WIN
        QString scheme = "file:///";
#else
        QString scheme = "file://";
#endif
        if (path.scheme().isEmpty())
            QDesktopServices::openUrl(QUrl('"' + scheme + path.toString() + '"'));
        else
            QDesktopServices::openUrl(path);
    }


    inline void email (const QString &address) {
            // открывает окно отправки email с помощью QDesktopServices::openUrl
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        if (!address.startsWith("mailto:",Qt::CaseInsensitive))
            QDesktopServices::openUrl(QUrl("mailto:" + address));
        else
            QDesktopServices::openUrl(QUrl(address));
    }

    inline void email (QUrl address) {
            // открывает окно отправки email с помощью QDesktopServices::openUrl
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        if (address.scheme().isEmpty())
            address.setScheme("mailto");
        QDesktopServices::openUrl(address);
    }


    inline void http (const QString &address) {
            // открывает url с помощью QDesktopServices::openUrl
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        if (! (address.startsWith("http://", Qt::CaseInsensitive) || address.startsWith("https://", Qt::CaseInsensitive)) )
            QDesktopServices::openUrl(QUrl("http://" + address));
        else
            QDesktopServices::openUrl(QUrl(address));
    }

    inline void http (const QUrl &address) {
            // открывает url с помощью QDesktopServices::openUrl
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        if (address.scheme().isEmpty())
            QDesktopServices::openUrl(QUrl("http://" + address.toString()));
        else
            QDesktopServices::openUrl(address);
    }


    inline void ftp (const QString &address) {
            // открывает url с помощью QDesktopServices::openUrl
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        if (!address.startsWith("ftp://", Qt::CaseInsensitive))
            QDesktopServices::openUrl(QUrl("ftp://" + address));
        else
            QDesktopServices::openUrl(QUrl(address));
    }

    inline void ftp (const QUrl &address) {
            // открывает url с помощью QDesktopServices::openUrl
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        if (address.scheme().isEmpty())
            QDesktopServices::openUrl(QUrl("ftp://" + address.toString()));
        else
            QDesktopServices::openUrl(address);
    }


    inline void openWithoutModifiers(const QString &request) {
            // открывает запрос request в программе, предназначенной для этого по умолчанию
            // в отличие от url(), email() и др., не модифицмрует запрос
        QDesktopServices::openUrl(QUrl(request));
    }

    inline void openWithoutModifiers(const QUrl &url) {
        QDesktopServices::openUrl(url);
    }


    inline bool run (const QString &name, const QStringList &list) {
            // выполняет программу name с параметрами list
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        QProcess pr;
        return pr.startDetached(name, list);
    }

    inline bool run (const QString &name) {
            // выполняет программу name
            // возвращает результат, возвращаемый функцией QProcess::startDetached()
        QProcess pr;
        return pr.startDetached(name);
    }

    inline QStringList systemsystemEnvironment () {
        return QProcessEnvironment::systemEnvironment().toStringList();
    }

    inline QString systemEnvironmentVariable (const QString &name) {
        return QProcessEnvironment::systemEnvironment().value(name);
    }

    void readMappedFile (const QString &name, QMap<QString, QString> *result);

    void readListFile (const QString &name, QStringList *result);

    void readListFile (const QString &name, QSet<QString> *result);

    inline bool isCorrectPath (const QString &path) {
            // функция возвращает, является ли введенная строка путем
            // на Windows путем ситается строка, которая начинается с любой буквы, за которой затем идут символы ':\'
            // на *NIX-системах - строка, которая начинается с '/'
#ifdef Q_OS_WIN
        QRegExp rx("[A-Za-z]:\\");
        return rx.indexIn(path) == 0;
#else
        QRegExp rx("/*",Qt::CaseInsensitive, QRegExp::Wildcard);
        return rx.exactMatch(path);
#endif
    }
}

#endif // OSTOOLS_H
