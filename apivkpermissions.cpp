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

#include "apivkpermissions.h"

ApiVKPermissions::ApiVKPermissions(int permsList)
{
    if (m_stringToIntMap.isEmpty() || m_intToStringMap.isEmpty()) {
        setupMaps();
    }

    m_permissions = permsList;
}

ApiVKPermissions::ApiVKPermissions(QString permsList, const QString &separator)
{
    if (m_stringToIntMap.isEmpty() || m_intToStringMap.isEmpty()) {
        setupMaps();
    }

    fromString(permsList, separator);
}

ApiVKPermissions::ApiVKPermissions(QStringList permsList)
{
    if (m_stringToIntMap.isEmpty() || m_intToStringMap.isEmpty()) {
        setupMaps();
    }

    fromStringList(permsList);
}

void ApiVKPermissions::setupMaps() {
    // Creating m_stringToIntMap
    m_stringToIntMap["notify"] = notify;
    m_stringToIntMap["friends"] = friends;
    m_stringToIntMap["photos"] = photos;
    m_stringToIntMap["audio"] = audio;
    m_stringToIntMap["video"] = video;
    m_stringToIntMap["docs"] = docs;
    m_stringToIntMap["notes"] = notes;
    m_stringToIntMap["pages"] = pages;
    m_stringToIntMap["wall"] = wall;
    m_stringToIntMap["groups"] = groups;
    m_stringToIntMap["messages"] = messages;
    m_stringToIntMap["notifications"] = notifications;
    m_stringToIntMap["status"] = status;
    m_stringToIntMap["stats"] = stats;
    m_stringToIntMap["ads"] = ads;
    m_stringToIntMap["offline"] = offline;

    // Creating m_intToStringMaps
    for (auto i = m_stringToIntMap.constBegin(); i != m_stringToIntMap.constEnd(); ++i) {
        m_intToStringMap[i.value()] = i.key();
    }
}

QStringList ApiVKPermissions::itemsToStringList(int permsIntList) {
    QStringList permsStringList;
    for (auto i = m_intToStringMap.constBegin(); i != m_intToStringMap.constEnd(); ++i) {
        if (permsIntList & i.key())
            permsStringList << i.value();
    }
    return permsStringList;
}

int ApiVKPermissions::itemsToInt(const QStringList &permsStringList) {
    int permsIntList = 0;
    for (auto i = m_stringToIntMap.constBegin(); i != m_stringToIntMap.constEnd(); ++i) {
        if (permsStringList.contains(i.key()))
            permsIntList |= i.value();
    }
    return permsIntList;
}

QString ApiVKPermissions::itemToString(int item) {
    for (auto i = m_intToStringMap.constBegin(); i != m_intToStringMap.constEnd(); ++i) {
        if (item == i.key())
            return i.value();
    }
    return "";
}

int ApiVKPermissions::itemToInt(const QString &item) {
    for (auto i = m_stringToIntMap.constBegin(); i != m_stringToIntMap.constEnd(); ++i) {
        if (item == i.key())
            return i.value();
    }
    return nothing;
}

