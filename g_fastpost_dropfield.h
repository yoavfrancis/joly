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

#ifndef DROPFIELD_H
#define DROPFIELD_H

#include "ui_g_fastpost_dropfield.h"
#include <QPointer>
#include <QUrl>
#include <QList>
#include <QMimeData>
#include <QDebug>
#include "g_fastpost_fileicon.h"
#include "ostools_userfilesinterface.h"

class DropField : public QFrame, private Ui::DropField
{
    Q_OBJECT
    
public:
    explicit DropField(QWidget *parent = 0);

    void setContentForMimeData(const QMimeData *mime);

    bool areAppropriateFiles(const QList<QUrl> &files);

protected:
//    void setupUi();
    void setContent(const QString &label);


private:
    enum { squareSide = 150 };

    QMap<QString, QPixmap> m_cashedPixmaps; // didn't make yet

    QMap<OSTools::UserFilesInterface::FileKind, QString> m_contentLabels;

    struct anonymous {
        FileIcon *fileIcon;
        QLabel *dropLabel;

        anonymous() : fileIcon(0), dropLabel(0) { }
    } ui;
};

#endif // DROPFIELD_H
