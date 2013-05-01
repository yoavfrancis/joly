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

class _LineEdit: public QLineEdit
{
    Q_OBJECT

public:
    _LineEdit(QWidget* parent = 0);

    inline void addCurrentToHistory() {
            // добавляет текущее значение текста в историю команд
        *history << text();
        currIndex++;
    }

    inline QStringList getHistory() const {
        return *history;
    }

    inline void setHistory(QStringList h) {
        *history = h;
    }

   inline  qint32 getCurrIndex() const {
        return currIndex;
    }

    inline void setCurrIndex(qint32 i) {
        currIndex = i;
    }

signals:
    void keyUpPressed();
    void keyDownPressed();
    void escapePressed();

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    QStringList *history;   // история команд
    qint32 currIndex;       // текущий индекс в истории команд
    bool upWasPressed;      // нажималась ли клавиша Вверх после последнего нажатия клавиши Enter
    QString lastText;       // последний введенный текст
};
#endif // GLLINEEDIT_H
