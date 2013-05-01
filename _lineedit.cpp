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

#include <QtWidgets>
#include "_lineedit.h"

_LineEdit::_LineEdit(QWidget* parent) : QLineEdit (parent)
{
    history = new QStringList;
    currIndex = history->size();
}

void _LineEdit::keyPressEvent(QKeyEvent* event) {
        // обеспечивает перехват событий нажатия клавиш Ctrl+Вверх и Ctrl+Вниз
        // для поддержки работы с историей ввода
    switch (event->key()) {

    case Qt::Key_Up:
        emit keyUpPressed();
        break;

    case Qt::Key_Down:
        emit keyDownPressed();
        break;

    case Qt::Key_Escape:
        emit escapePressed();

    default:
        QLineEdit::keyPressEvent(event);
    }
}
