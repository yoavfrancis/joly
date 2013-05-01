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

#include "ostools_userfilesinterface.h"
#include <QtCore>

QMap<QString, QString> OSTools::UserFilesInterface::m_files;

QMap<QString, QString> updateFilesList()
{
    static QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString homeDir;
#ifdef Q_OS_WIN
    homeDir = QDir::fromNativeSeparators(env.value("USERPROFILE"));
#else
    homeDir = env.value("HOME");
#endif

    QDirIterator it(homeDir, QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
    QMap<QString, QString> result;

    while (it.hasNext()) {
        it.next();
        if (!it.fileInfo().isHidden() && it.fileName() != "." && it.fileName() != "..")
            result.insertMulti(it.fileName(), it.fileInfo().canonicalFilePath());
    }

    return result;
}

///////////////////////////////////////////

OSTools::UserFilesInterface::UserFilesInterface(QObject *parent) :
    QObject(parent)
{
    if (m_files.isEmpty()) {
        update();
    }
}

bool OSTools::UserFilesInterface::isContanedInUserFolder(const QString &fileName)
{
    return !m_files.values(fileName).isEmpty();
}

OSTools::UserFilesInterface::FileKind OSTools::UserFilesInterface::getFileKind(const QString &filePath) {
    QFileInfo fileInfo(filePath);
    QString extension = fileInfo.suffix().toLower();

    // Images
    QStringList imagesExtensionsList;
    imagesExtensionsList << "jpg" << "jpeg" << "bmp" << "png" << "gif";

    if (imagesExtensionsList.contains(extension))
        return FileKind::image;

    // Audio
    QStringList audioExtensionsList;
    audioExtensionsList << "mp3" << "wma" << "wav" << "ogg" << "oga";

    if (audioExtensionsList.contains(extension))
        return FileKind::audio;

    // Video
    QStringList videoExtensionsList;
    videoExtensionsList << "mpg" << "avi" << "3gp" << "ogg" << "ogv";

    if (videoExtensionsList.contains(extension))
        return FileKind::video;

    // Executable
    if (fileInfo.isExecutable())
        return FileKind::executable;

    // Other
    return FileKind::other;
}

QStringList OSTools::UserFilesInterface::filesList(const QString &filter)
{
    if (filter.isEmpty())
        return m_files.values();

    if (filter.contains(QDir::separator()))
        return QStringList();

    QStringList result;
    for (auto iter = m_files.constBegin(); iter != m_files.constEnd(); ++iter) {
        if (iter.key().contains(filter))
            result.append(iter.value());
    }

    return result;
}

void OSTools::UserFilesInterface::update()
{
    bool entriesListWasEmpty = m_files.isEmpty();
    m_files = updateFilesList();
    if (entriesListWasEmpty)
        emit filesAreAvailable();
}
