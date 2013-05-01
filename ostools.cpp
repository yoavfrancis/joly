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

#include "ostools.h"
#include <iostream>

namespace OSTools {

    void searchInInternet(const QString &what) {
        QUrl tmp("http://google.com/search");
//        QUrl query(what);
//        QByteArray str = query.toEncoded();
//        str.replace("+","%252B");
//        str.replace(' ', '+');
        tmp.addQueryItem("q", what);
        QDesktopServices::openUrl(tmp);
    }

    void readMappedFile (const QString &name, QMap<QString, QString> *result) {
            // функция читает файл со строками вида СЛОВО СЛОВО
            // и возвращает его в параметре result как QMap<QString, QString>*
        QFile file(name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return;
        }

        QTextStream in(&file);
        QStringList lineList;
        QString line = in.readLine();
        while (!line.isNull()) {
            line = line.simplified();
            lineList = line.split(' ');
            result->insert(lineList[0],lineList[1]);
            line = in.readLine();
        }
    }

    void readListFile (const QString &name, QStringList *result) {
            // функция читает файл вида СЛОВО\nСЛОВО\nСЛОВО ...
            // и возвращает его в параметре result как QStringList*
        QFile file(name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << qPrintable(QObject::tr("Невозможно открыть файл для чтения: "))
                      << qPrintable(file.errorString()) << std::endl;
            return;
        }

        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            line = line.simplified();
            line = line.toLower();
            if (line[0] == '#') {
                line = in.readLine();
                continue; // пропуск комментариев
            }
            result->append(line);
            line = in.readLine();
        }
    }

    void readListFile (const QString &name, QSet<QString> *result) {
            // функция читает файл вида СЛОВО\nСЛОВО\nСЛОВО ...
            // и возвращает его в параметре result как QStringList*
        QFile file(name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            std::cerr << qPrintable(QObject::tr("Невозможно открыть файл для чтения: "))
                      << qPrintable(file.errorString()) << std::endl;
            return;
        }

        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            line = line.simplified();
            line = line.toLower();
            if (line[0] == '#') {
                line = in.readLine();
                continue; // пропуск комментариев
            }
            result->insert(line);
            line = in.readLine();
        }
    }
}

