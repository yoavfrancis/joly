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

#include "strtools.h"
#include <QObject>
#include <QUrl>
#include <QSet>
#include <QDir>
#include "consts.h"

QString StrTools::getFirstWord (const QString& str) {
        // возвращает первое слово в строке или всю строку, если она - одно слово
        // разделителями слов считаюся пробелы
    QString res;
    int spPos;
    spPos = str.indexOf(' ');
    if (spPos == -1) return str; // если снова ничего не нашел
    res = str;
    res.remove(spPos, str.length()-1);
    return res;
}

bool StrTools::runAbbr(const QString &str) {
        // анализирует слово в качестве сокращения поиска и выполняет нужные действия
        // возвращает false, если ничего не сделано, и true, если что-то сделано
    QString word = StrTools::getFirstWord(str);
    QString tmp;
    if (word == "!run") {
        tmp = str;
        tmp.remove(0, 4); // удаляем с начала на длину слова "run" с пробелом
        OSTools::run(tmp);
        return true;
    } else if (tmp == "!help") {
        OSTools::notifySend(QObject::tr("Help \"Help is not available now. Sorry...\""));
        return true;
    }
    return false;
}

bool StrTools::fastRun(const QString& str, QMap<QString,QString>* base) {
    if (base->contains(str.toLower())) {
        QString s = base->value(str.toLower());
        OSTools::run(s);
        return true;
    }
    return false;
}

QString StrTools::getFirstLevelDomain(const QUrl &url) {
        // возвращает домен первого уровня
    QStringList list = url.host().split('.');             // разбиваем хост по доменам
    return list.last();
}

bool StrTools::isCorrectHttp(const QUrl &url, const QSet<QString>* const dL) {
    QString str = url.toString();
    bool mainFlag = url.isValid() &&
            (url.scheme() == "http" || url.scheme() == "https" || url.scheme().isEmpty()) &&
            !QDir::isAbsolutePath(str) &&
            str.indexOf('.') != -1 &&
            str.left(1) != "." &&
            str.right(1) != "." &&
            str.indexOf('@') == -1;

    if (dL) {
        if (domainIsValid(getFirstLevelDomain(url), dL))
            return mainFlag;
        else
            return false;
    } else {
        return mainFlag;
    }
}

bool StrTools::isCorrectDomainName(const QString &name) {
    QStringList charList = QString("' + . , | ! \" £ $ % & / ( ) = ? ^ * ç ° § ; : _ > ] [ @").split(' ');
    charList << " ";
    bool ok = true;
    forc11 (QString str, charList) {
        if (name.contains(str))
            ok = false;
    }
    return ok;

}

bool StrTools::isCorrectEmail(const QUrl &url, const QSet<QString>* const dL) {
    QString str = url.toString();
    bool mainFlag = url.isValid() &&
            (url.scheme() == "mailto" || url.scheme().isEmpty()) &&
            !QDir::isAbsolutePath(str) &&
            str.indexOf('.') != -1 &&
            str.left(1) != "." &&
            str.right(1) != "." &&
            str.indexOf('@') != -1 &&
            str.left(1) != "@" &&                         // @ не первая
            str.right(1) != "@";   // @ не последняя

    if (dL) {
        if (domainIsValid(getFirstLevelDomain(url), dL))
            return mainFlag;
        else
            return false;

    } else {
        return mainFlag;
    }
}

bool StrTools::isCorrectFtp(const QUrl &url, const QSet<QString>* const dL) {
    QString str = url.toString();
    bool mainFlag = url.isValid() &&
            url.scheme() == "ftp" &&
            !QDir::isAbsolutePath(str) &&
            str.indexOf('.') != -1;

    if (dL) {
        if (domainIsValid(getFirstLevelDomain(url), dL))
            return mainFlag;
        else
            return false;

    } else {
        return mainFlag;
    }
}

bool StrTools::isCorrectTwiUser(const QString &str) {
    return QRegExp ("@\\w+").exactMatch(str);
}
