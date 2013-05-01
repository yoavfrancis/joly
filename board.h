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

#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPointer>

#include <QTimer>

class G_GlobalLine;
class G_Messages;
class G_FastPost;
class QUrl;
class QMainWindow;
class QSystemTrayIcon;
class QMenu;
class SettingsWidget;
class QApplication;

class Board : public QObject
{
    Q_OBJECT

public:
    Board(QApplication *a);
    ~Board();

public slots:
    void show();
    void valueChanged(const QString &gadget, const QString &valueName, const QVariant &value);

protected:
    QMenu *createMenuForTrayIcon();

private:
    QApplication *app;
    QPointer<G_GlobalLine> globLineGadget;
    QPointer<G_Messages> messagesGadget;
    QPointer<G_FastPost> fastPostGadget;
//    QMainWindow *window;

    QPointer<QSystemTrayIcon> trayIcon;
    QPointer<SettingsWidget> settingsWidget;
};

#endif // BOARD_H
