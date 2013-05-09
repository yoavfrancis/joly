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

#include "g_fastpost_dropfield.h"
#include <QtCore>
#include "imgtools.h"
#include "consts.h"


#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

DropField::DropField(QWidget *parent) :
    QFrame(parent)
{
    setupUi(this);
    /*ui.*/fileIcon->setSideSize(squareSide);

    m_contentLabels[OSTools::UserFilesInterface::FileKind::unknown] = "";
    m_contentLabels[OSTools::UserFilesInterface::FileKind::image] = tr("Ваше изображение", "drop <text> here");
    m_contentLabels[OSTools::UserFilesInterface::FileKind::audio] = tr("Вашу аудиозапись", "drop <text> here");
    m_contentLabels[OSTools::UserFilesInterface::FileKind::video] = tr("Вашу видеозапись", "drop <text> here");
    m_contentLabels[OSTools::UserFilesInterface::FileKind::other] = tr("Ваш файл", "drop <text> here");
}

void DropField::setContentForMimeData(const QMimeData *mime) {
    if (mime->hasUrls()) {

        QList<QUrl> urlsList = mime->urls();

        if (urlsList.length() == 1) {
#ifdef Q_OS_LINUX
            QString fileName = urlsList.first().toString().remove("file://");
#elif defined Q_OS_WIN
            QString fileName = urlsList.first().toString().remove("file:///");
#else
#error Unsupported OS
#endif
            try {
                /*ui.*/fileIcon->setContentFromFile(fileName);
                setContent(m_contentLabels[OSTools::UserFilesInterface::getFileKind(fileName)]);
            } catch (FileIcon::FileDoesntExist e) {
                qWarning() << "Dragged file doesn't exist:" << e.filePath;
            }

            return;
        }

        QMap<OSTools::UserFilesInterface::FileKind, uint> kindsCount;

        // counting how many files of each kind
        foreach (const QUrl &url, urlsList) {
            OSTools::UserFilesInterface::FileKind currKind = OSTools::UserFilesInterface::FileKind(OSTools::UserFilesInterface::getFileKind(url.toString().remove("file://")));
            ++kindsCount[currKind];
        }

        if (kindsCount.size() == 1) {
            OSTools::UserFilesInterface::FileKind singleKind = kindsCount.keys().first();

            switch (singleKind) {

            case OSTools::UserFilesInterface::FileKind::image:
            {
                /*ui.*/fileIcon->setContentFromPixmap(QPixmap(":/images/images.png"));
                setContent(tr("Ваши изображения", "drop <text> here"));
                return;
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

            }
        }
        else {
            /*ui.*/fileIcon->setContentFromPixmap(QPixmap(":/images/files.png"));
            setContent(tr("Ваши файлы", "drop <text> here"));
        }
    } // if (mime->hasUrls())
    else if (mime->hasImage()) {
        QImage image = qvariant_cast<QImage>(mime->imageData());
        /*ui.*/fileIcon->setContentFromPixmap(QPixmap().fromImage(image));
        setContent(tr("Ваше изображение", "drop <text> here"));
    } // if (mime->hasImage())
    else {
        Q_ASSERT_X(false, "DropField", "else runned");
    }
}

bool DropField::areAppropriateFiles(const QList<QUrl> &files) {
    if (files.isEmpty())
        return false;

    foreach (const QUrl &url, files) {
#ifdef WIN_OLD_COMPILER
        OSTools::UserFilesInterface::FileKind currKind = OSTools::UserFilesInterface::getFileKind(url.toString().remove("file://"));
        if (int(currKind) != int(OSTools::UserFilesInterface::image))
#else
        OSTools::UserFilesInterface::FileKind currKind = OSTools::UserFilesInterface::FileKind(OSTools::UserFilesInterface::getFileKind(url.toString().remove("file://")));
        if (currKind != OSTools::UserFilesInterface::FileKind::image)
#endif
            return false;
    }

    return true;
}

void DropField::setContent(const QString &label) {
    /*ui.*/dropLabel->setText(tr("Отпустите %1 здесь", "Message in drop field in Messages Gadget").arg(label));
    //    dropImage->setPixmap(m_pixmap);
}

//void DropField::setupUi() {
//    ui.fileIcon = new FileIcon(0, this);
//    ui.fileIcon->setBorder("3px solid #333");
//    ui.dropLabel = new QLabel;
//    QFont font = ui.dropLabel->font();
//    font.setBold(true);
//    ui.dropLabel->setFont(font);

//    QHBoxLayout *firstHLayout = new QHBoxLayout;
////    firstHLayout->addStretch(40);
//    firstHLayout->addWidget(ui.fileIcon);
////    firstHLayout->addStretch(40);

//    QHBoxLayout *secondHLayout = new QHBoxLayout;
////    secondHLayout->addStretch(40);
//    secondHLayout->addWidget(ui.dropLabel);
////    secondHLayout->addStretch(40);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addLayout(firstHLayout);
////    mainLayout->addStretch(40);
//    mainLayout->addLayout(secondHLayout);
//}

