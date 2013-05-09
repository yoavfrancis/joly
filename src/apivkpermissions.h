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

#ifndef APIVKPERMISSIONS_H
#define APIVKPERMISSIONS_H

#include <QtCore>

class ApiVKPermissions
{
public:
    ApiVKPermissions(int permsList);
    ApiVKPermissions(QString permsList, const QString &separator = QString(','));
    ApiVKPermissions(QStringList permsList);

    inline int toInt() {
        return m_permissions;
    }

    inline void fromInt(int permsList) {
        m_permissions = permsList;
    }

    inline QString toString(const QString &separator = QString(',')) {
        return toStringList().join(separator);
    }

    inline void fromString(const QString &permsList, const QString &separator = QString(',')) {
        fromStringList(permsList.split(separator));
    }

    inline QStringList toStringList() {
        return itemsToStringList(m_permissions);
    }

    inline void fromStringList(const QStringList &permsList) {
        m_permissions = itemsToInt(permsList);
    }

    inline bool contains(int value) {
        return m_permissions & value;
    }

    inline bool contains(const QString &value, const QString &separator = QString(',')) {
        return this->contains(value.split(separator));
    }

    inline bool contains(const QStringList &values) {
            // возвращает true, если в списке разрешений в классе содержатся ВСЕ разрешения, переданные в values
            // иначе - false
        for (QStringList::const_iterator i = values.constBegin(); i != values.constEnd(); ++i) {
            if (!(m_permissions & itemToInt(*i)))
                return false;
        }
        return true;
    }

    inline void add(int value) {
        m_permissions |= value;
    }

    inline void add(const QString &value, const QString &separator = QString(',')) {
        this->add(value.split(separator));
    }

    void add(const QStringList &values) {
        for (QStringList::const_iterator i = values.constBegin(); i != values.constEnd(); ++i) {
            m_permissions |= itemToInt(*i);
        }
    }

    inline void remove(int value) {
        m_permissions ^= value;
    }

    inline void remove(const QString &value, const QString &separator = QString(',')) {
        this->remove(value.split(separator));
    }

    inline void remove(const QStringList &values) {
        for (QStringList::const_iterator i = values.constBegin(); i != values.constEnd(); ++i) {
            m_permissions ^= itemToInt(*i);
        }
    }

    enum perms { nothing = 0x0000, notify = 0x0001, friends = 0x0002, photos = 0x0004, audio = 0x0008,
                 video = 0x0010, docs = 0x0020, notes = 0x0040, pages = 0x0080, wall = 0x0100, groups = 0x0200,
                 messages = 0x0400, notifications = 0x0800, status = 0x1000, stats = 0x2000, ads = 0x4000, offline = 0x8000, all = 0xFFFF };

protected:
    void setupMaps();

    QStringList itemsToStringList(int permsIntList);
    int itemsToInt(const QStringList &permsStringList);
    QString itemToString(int item);
    int itemToInt(const QString &item);

private:
    int m_permissions;
    QMap<QString, int> m_stringToIntMap;
    QMap<int, QString> m_intToStringMap;
};

#endif // APIVKPERMISSIONS_H
