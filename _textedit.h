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

#ifndef _TEXTEDIT_H
#define _TEXTEDIT_H

#include <QTextEdit>

/**
 * @brief The _TextEdit class is a descendant class of QTextEdit with several additional features.
 */
class _TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit _TextEdit(QWidget *parent = 0) : QTextEdit(parent) { }
    
signals:
    void droppingFinished();

protected:
    void dropEvent(QDropEvent *e) {
        emit droppingFinished();
        QTextEdit::dropEvent(e);
    }
};

#endif // _TEXTEDIT_H
