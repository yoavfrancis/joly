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

#ifndef _LINEEDIT_H
#define _LINEEDIT_H

#include <QObject>
#include <QLineEdit>

class QWidget;
class QStringList;
class QKeyEvent;

/**
 * @brief The _LineEdit class is a descendant class of QLineEdit with several additional features.
 */
class _LineEdit: public QLineEdit
{
    Q_OBJECT

public:
    _LineEdit(QWidget* parent = 0);

signals:
    void keyUpPressed();
    void keyDownPressed();
    void escapePressed();

protected:
    void keyPressEvent(QKeyEvent* event);

private:

};
#endif // GLLINEEDIT_H
