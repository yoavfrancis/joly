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

#ifndef G_FASTPOST_ATTACHEDFILE_H
#define G_FASTPOST_ATTACHEDFILE_H

#include "ui_g_fastpost_fileicon.h"
#include "consts.h"
#include "imgtools.h"

class FileIcon : public QLabel/*, private Ui::FileIcon*/
{
    Q_OBJECT
    
public:
    explicit FileIcon(QWidget *parent = 0);
    explicit FileIcon(uint sideSize = 0, QWidget *parent = 0);

    void setContentFromFile(QString filePath, uint sideSize = 0);

    void setContentFromPixmap(const QPixmap &pixmap, uint sideSize = 0);

    void setBorder(const QString &cssValue);

    void setSideSize(uint size);

    inline uint getSideSize() {
        return m_sideSize;
    }

    class FileDoesntExist {
    public:
        FileDoesntExist(QString s) {
            filePath = s;
        }

        QString filePath;
    };

protected:
    inline void setPixmapToLabel() {
        setPixmap(m_fileIcon);
    }

private:
    enum { squareSideSize = 150 };
    QPixmap m_fileIcon;
    uint m_sideSize;
};

#endif // G_FASTPOST_ATTACHEDFILE_H
