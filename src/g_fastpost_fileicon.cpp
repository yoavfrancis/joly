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

#include "g_fastpost_fileicon.h"
#include <QtCore>
#include "ostools_userfilesinterface.h"
#include "imgtools.h"

FileIcon::FileIcon(uint sideSize, QWidget *parent) :
    QLabel(parent), m_sideSize(sideSize)
{
//    setupUi(this);
}

FileIcon::FileIcon(QWidget *parent) :
    QLabel(parent), m_sideSize(0)
{
}

void FileIcon::setContentFromFile(QString filePath, uint sideSize) {
    uint size;
    if (sideSize == 0) {
        if (m_sideSize == 0)
            size = squareSideSize;
        else
            size = m_sideSize;
    } else {
        size = sideSize;
    }

    if (!QFileInfo(filePath).exists()) {
        throw FileDoesntExist(filePath);
    }
    OSTools::UserFilesInterface::FileKind fileKind = OSTools::UserFilesInterface::getFileKind(filePath);

    switch (fileKind) {
    case OSTools::UserFilesInterface::FileKind::image:
    {
        if (Q_UNLIKELY(!m_fileIcon.load(filePath))) {
            QString problem = "Unknown problems with loading pixmap from file in FileIcon class";
            Q_ASSERT_X(false, "FileIcon::setContentFromFile", qPrintable(problem));
            qWarning() << problem;
        }
        ImgTools::scaleToSize(&m_fileIcon, size);
        ImgTools::cropCenterSquare(&m_fileIcon, size);
    }

    case OSTools::UserFilesInterface::FileKind::audio:
    {
        // nothing yet
    }

    case OSTools::UserFilesInterface::FileKind::video:
    {
        // nothing yet
    }

    default:
        //  doing nothing
        ;

    } // switch (fileKind)

    setPixmapToLabel();
}

void FileIcon::setContentFromPixmap(const QPixmap &pixmap, uint sideSize) {
    uint size;
    if (sideSize == 0) {
        if (m_sideSize == 0)
            size = squareSideSize;
        else
            size = m_sideSize;
    } else {
        size = sideSize;
    }

    m_fileIcon = pixmap;
    ImgTools::scaleToSize(&m_fileIcon, size);
    ImgTools::cropCenterSquare(&m_fileIcon, size);

    setPixmapToLabel();
}

void FileIcon::setBorder(const QString &cssValue) {
    QString css = /*label->*/styleSheet();

    if (css.contains("border")) {
        int startPosition = css.indexOf("border:") + QString("border:").length();
        int endPosition = css.indexOf(';', startPosition);

        css.replace(startPosition, endPosition - startPosition, cssValue);
        /*label->*/setStyleSheet(css);
    } else {
        /*label->*/setStyleSheet(css + "\nborder: " + cssValue + ';');
    }
}

void FileIcon::setSideSize(uint size) {
    uint oldSize = m_sideSize;
    m_sideSize = size;

    if (m_fileIcon.isNull())
        return;

    if (size != oldSize) {
        ImgTools::scaleToSize(&m_fileIcon, size);
        setPixmapToLabel();
    }
}
