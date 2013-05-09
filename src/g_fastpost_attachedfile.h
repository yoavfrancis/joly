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

#ifndef G_FASTPOST_ATTACHEDFILEICON_H
#define G_FASTPOST_ATTACHEDFILEICON_H

#include <QWidget>
#include "g_fastpost_fileicon.h"
#include <QPointer>
#include <QTimer>

#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

class QPushButton;


class AttachedFile : public QWidget
{
    Q_OBJECT

public:
    explicit AttachedFile(QString filePath, uint id, QWidget *parent = 0);

    inline QString getFilePath() const {
        return m_filePath;
    }

    inline void setFilePath(QString filePath) {
        m_filePath = filePath;
        setupUi(true);  // recreating ui
    }

    inline bool isWaitingForRestore() const {
        return m_isWaitingForRestore;
    }
    
signals:
    void removed(uint id);
    
public slots:

protected:
    void setupUi(bool recreate = false);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void setBackgroundColor(QString color);
    void restoreBackgroundColor();


    // if widget waits for restoring, it returnes "color: " + Consts::Colors::grey + ";";
    // else - ""
    inline QString getStyleSheetForRightColor() const {
        if (isWaitingForRestore())
            return "color: " + Consts::Colors::grey + ";";
        else
            return "";
    }

protected slots:
    void waitForRestore();
    void restore();
    inline void remove() {
        emit removed(m_id);
    }

private:
    enum { sideSize = 24 };

    struct anonymous {
        FileIcon *icon;
        QLabel *text;
        QPushButton *removeButton;
        QPushButton *restoreButton;

        anonymous() : icon(nullptr), text(nullptr), removeButton(nullptr), restoreButton(nullptr) { }
    } ui;

    QString m_filePath;
    uint m_id;

    bool m_isWaitingForRestore;
    QTimer m_restoreTimer;
};

#endif // G_FASTPOST_ATTACHEDFILEICON_H
