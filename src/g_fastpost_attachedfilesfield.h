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

#ifndef G_FASTPOST_ATTACHEDFILESFIELD_H
#define G_FASTPOST_ATTACHEDFILESFIELD_H

#include <QWidget>
#include "g_fastpost_attachedfile.h"
#include <QPointer>
#include <QList>

class AttachedFilesField : public QWidget
{
    Q_OBJECT
public:
    explicit AttachedFilesField(QWidget *parent = 0);
    explicit AttachedFilesField(const QStringList &filesList, QWidget *parent = 0);

    void addFile(QString filePath);
    void removeFile(QString filePath);
    bool hasFile(QString filePath) const;
    void clear();

    QString fileAt(int pos) const;
    QStringList getFilesList() const;
    void setFilesList(const QStringList &filesList);
    inline bool isEmpty() const { return filesCount() == 0; }
    inline uint filesCount() const { return ui.filesList.length(); }

signals:
    void becomedNotEmpty();
    void becomedEmpty();
    void fileRemoved();
    
public slots:

protected:
    void setupUi();
    void removeFileById(uint id);
    inline void hideIfEmpty() { if (m_realCount == 0) hide(); }

protected slots:
    void removed(uint id);

private:
    bool m_hasUi;
    uint m_freeId;
    uint m_realCount;
    struct _ui {
        QList<QPointer<AttachedFile> > filesList;
    } ui; 
};

#endif // G_FASTPOST_ATTACHEDFILESFIELD_H
