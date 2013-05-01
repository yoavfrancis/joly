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

#ifndef STRTOOLS_H
#define STRTOOLS_H

#include <QMap>
#include <QString>
#include <QChar>
#include <QSet>
#include "ostools.h"

class QUrl;

namespace StrTools {
    const char noMatch = '-';

    QString getFirstWord (const QString& str);

    bool runAbbr(const QString &str);

    bool fastRun(const QString& str, QMap<QString,QString>* base);

    inline bool hasSpaces(const QString& str) {
            // анализирует наличие пробелов в строке
            // возвращает true, если пробелы есть, и false, если их нет
        return !(str.indexOf(' ') == -1);
    }

    inline bool isSymbol(const QString& str, QChar ch) {
            // анализирует наличие пробелов в строке
            // возвращает true, если пробелы есть, и false, если их нет
        return !(str.indexOf(ch) == -1);
    }

    inline bool isTextAtBegin (const QString& word, const QString& str) {
            // анализирует наличие слова word в начале строки str
            // возвращает true, если слово word в начале строки atr имеется, иначе - false
        return str.indexOf(word) == 0;
    }

    inline char dig2char(int i) {
        switch (i) {
            case 0: return '0'; break;
            case 1: return '1'; break;
            case 2: return '2'; break;
            case 3: return '3'; break;
            case 4: return '4'; break;
            case 5: return '5'; break;
            case 6: return '6'; break;
            case 7: return '7'; break;
            case 8: return '8'; break;
            case 9: return '9'; break;
            default: return noMatch;
        }
    }

    inline bool domainIsValid(QString domain, const QStringList* const dL = 0) {
        return dL->indexOf(domain) != -1;
    }

    inline bool domainIsValid(QString domain, const QSet<QString>* const dL = 0) {
        return dL->find(domain) != dL->constEnd();
    }

    QString getFirstLevelDomain(const QUrl &url);
    bool isCorrectHttp(const QUrl &url, const QSet<QString> *const dL= 0);
    bool isCorrectDomainName(const QString &name);
    bool isCorrectEmail(const QUrl &url, const QSet<QString> *const dL = 0);
    bool isCorrectFtp(const QUrl &url, const QSet<QString> *const dL = 0);
    bool isCorrectTwiUser(const QString &str);

//    QStringList toStringList(const QSet<QString> &set);
//    QSet<QString> toStringSet(const QStringList &list);
}

#endif // STRTOOLS_H
