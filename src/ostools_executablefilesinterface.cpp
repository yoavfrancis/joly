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

#include "ostools_executablefilesinterface.h"
#include "ostools.h"
#include <QProcessEnvironment>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

QStringList OSTools::ExecutablesInterface::m_pathDirs;
QSet<QString> OSTools::ExecutablesInterface::m_pathFiles;
QTimer OSTools::ExecutablesInterface::m_updateTimer;

OSTools::ExecutablesInterface::ExecutablesInterface(QObject *parent)
    : QObject(parent)
{
    if (m_pathDirs.isEmpty()) {
        QTimer *initTimer = new QTimer;
        initTimer->setSingleShot(true);
        connect(initTimer, SIGNAL(timeout()), SLOT(updateLists()));
        connect(initTimer, SIGNAL(timeout()), initTimer, SLOT(deleteLater()));
        initTimer->start(1);
    }

    if (!m_updateTimer.isActive()) {
        const qint32 millisecondsInHour = 3600000;
        connect(&m_updateTimer, SIGNAL(timeout()), SLOT(updateLists()));
        m_updateTimer.start(millisecondsInHour);
    }
}


void OSTools::ExecutablesInterface::updateLists() {
    updatePathDirsList();
    updatePathFilesList();
}

void OSTools::ExecutablesInterface::updatePathDirsList() {
#ifdef Q_OS_LINUX

    QProcessEnvironment systemEnvironment = QProcessEnvironment::systemEnvironment();
    const QString foldersSeparator = ":";
    const QString pathVarName = "PATH";
    m_pathDirs = systemEnvironment.value(pathVarName).split(foldersSeparator);

#elif defined(Q_OS_WIN)

    QProcessEnvironment systemEnvironment = QProcessEnvironment::systemEnvironment();
    const QString foldersSeparator = ";";
    const QString pathVarName = "PATH";
    m_pathDirs = systemEnvironment.value(pathVarName).split(foldersSeparator);

#else
#error This OS is not supported in OSTools::ExecutableFilesInterface class
#endif
}

void OSTools::ExecutablesInterface::updatePathFilesList() {
    m_pathFiles.clear();
    foreach (const QString &path, m_pathDirs) {
        QDir pathDir(path);

#ifdef Q_OS_WIN
        QStringList filters;
        filters << "*.exe" << "*.com" << "*.bat" << "*.cmd";
        QStringList filesList = pathDir.entryList(filters, QDir::Files | QDir::NoDot | QDir::NoDotDot);
#else
        QStringList filesList = pathDir.entryList(QDir::Files | QDir::NoDot | QDir::NoDotDot);
#endif
        m_pathFiles.unite(filesList.toSet());
    }
}

bool OSTools::ExecutablesInterface::isExecutable(const QString &fileName) const {
    if (fileName.contains(QDir::separator())) {
            // not just filename, but contains system separators; it can't be in path directories
        QFileInfo fileInfo(fileName);
        return fileInfo.isExecutable() && !fileInfo.isDir();
    } else {
            // most likely it's file in some of path directories
        for (QStringList::const_iterator nativeDirPath = m_pathDirs.constBegin(); nativeDirPath != m_pathDirs.constEnd(); ++nativeDirPath) {
            QString fullFilePath = QDir::fromNativeSeparators(*nativeDirPath);
            if (!fullFilePath.endsWith('/'))
                fullFilePath.append('/');
            fullFilePath.append(fileName);

            QFileInfo fileInfo(fullFilePath);

            if (fileInfo.isExecutable() && !fileInfo.isDir())
                return true;
        }
    }

    return false;
}

bool OSTools::ExecutablesInterface::run(const QString &fileName) const {
    return OSTools::run(fileName);
}

QStringList OSTools::ExecutablesInterface::executablesList(const QString &filter) {
    if (filter.isEmpty())
        return m_pathFiles.toList();

    QStringList resultList;
#ifdef WIN_OLD_COMPILER
    foreach(const QString &value, m_pathFiles) {
#else
    for (const QString &value : m_pathFiles) {
#endif
        if (value.startsWith(filter, Qt::CaseInsensitive))
            resultList.append(value);
    }
    return resultList;
}

