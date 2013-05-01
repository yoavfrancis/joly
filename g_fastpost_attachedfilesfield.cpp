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

#include "g_fastpost_attachedfilesfield.h"
#include <QtWidgets>

#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif


AttachedFilesField::AttachedFilesField(QWidget *parent) :
    QWidget(parent), m_hasUi(false)/*, m_lastId(0)*/, m_realCount(0)
{ }

AttachedFilesField::AttachedFilesField(const QStringList &filesList, QWidget *parent) :
    QWidget(parent), m_hasUi(false)/*, m_lastId(0)*/
{

    if (filesList.isEmpty())
        return;

    setFilesList(filesList);
}

/*
    Adding file "filePath" to files list and to UI.
    If file doesn't exist, we do nothing.
*/
void AttachedFilesField::addFile(QString filePath) {
    if (!QFileInfo(filePath).exists())
        return;

    if (!m_hasUi)
        setupUi();

    QPointer<AttachedFile> file = new AttachedFile(filePath, ui.filesList.length());
    ui.filesList.append(file);
    connect(file.data(), SIGNAL(removed(uint)), SLOT(removed(uint)));
    this->layout()->addWidget(file.data());

    if (m_realCount == 0)
        emit becomedNotEmpty();
    ++m_realCount;
}

void AttachedFilesField::removeFile(QString filePath) {
    for (auto iter = ui.filesList.begin(); iter != ui.filesList.end(); ++iter) {

        if ((*iter)->getFilePath() == filePath) {
            (*iter)->deleteLater();
            iter = 0;

            --m_realCount;
            hideIfEmpty();
            emit fileRemoved();
            if (m_realCount == 0)
                emit becomedEmpty();
            return;
        }

    }

}

bool AttachedFilesField::hasFile(QString filePath) const {
#ifdef WIN_OLD_COMPILER
    foreach (const QPointer<AttachedFile> &file, ui.filesList) {
#else
    for (const QPointer<AttachedFile> &file : ui.filesList) {
#endif
        if (file->getFilePath() == filePath)
            return true;
    }

    return false;
}

/*
    Cleares list of files and layout
*/
void AttachedFilesField::clear() {
    ui.filesList.clear();

    QLayout *layout = this->layout();
    if (layout == 0)
        return;

    while (layout->count() != 0) {
        layout->takeAt(0)->widget()->deleteLater();
    }

    hide();

    m_realCount = 0;
    emit becomedEmpty();
}

QString AttachedFilesField::fileAt(int pos) const {
    if (pos < 0 || ui.filesList.length() <= pos)
        return QString();

    return ui.filesList.at(pos)->getFilePath();
}


QStringList AttachedFilesField::getFilesList() const {
    QStringList result;
#ifdef WIN_OLD_COMPILER
    foreach (const QPointer<AttachedFile> &file, ui.filesList) {
#else
    for (const QPointer<AttachedFile> &file : ui.filesList) {
#endif
            if (file)
            if (!file->isWaitingForRestore()) // prevending possible segmentation fault in if (file && !file->isWaitingForRestore())
                result.append(file->getFilePath());
    }

    return result;
}

void AttachedFilesField::setFilesList(const QStringList &filesList) {
    clear();

    if (filesList.isEmpty())
        return;

#ifdef WIN_OLD_COMPILER
    foreach (const QString &filePath, filesList) {
#else
    for (const QString &filePath : filesList) {
#endif
        if (!QFileInfo(filePath).exists())
            continue;

        QPointer<AttachedFile> file = new AttachedFile(filePath, ui.filesList.length());
        ui.filesList.append(file);
        connect(file.data(), SIGNAL(removed(uint)), SLOT(removed(uint)));
    }

    m_realCount = ui.filesList.length();
    emit becomedNotEmpty();

    setupUi();

    show();
}

void AttachedFilesField::setupUi()
{
    if (!this->layout())
        setLayout(new QVBoxLayout);

    QLayout *layout = this->layout();
#ifdef WIN_OLD_COMPILER
    foreach (const QPointer<AttachedFile> &file, ui.filesList) {
#else
    for (const QPointer<AttachedFile> &file : ui.filesList) {
#endif
        if (file)
            layout->addWidget(file.data());
    }

    layout->setSpacing(2);

    setStyleSheet("background-color: " + Consts::Colors::lightestGrey);
    setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(Consts::Colors::lightestGrey));
    setPalette(pal);

    m_hasUi = true;
}

void AttachedFilesField::removed(uint id) {
    removeFileById(id);
}

void AttachedFilesField::removeFileById(uint id) {
    Q_ASSERT(id < uint(ui.filesList.length()));
    ui.filesList.at(id)->deleteLater();
    ui.filesList[id] = 0;

    --m_realCount;
    hideIfEmpty();
    emit fileRemoved();
    if (isEmpty())
        emit becomedEmpty();
}
