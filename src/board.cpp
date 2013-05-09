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
#include <QWebView>
#include <QtNetwork/QNetworkRequest>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include "board.h"
#include "g_globalline.h"
#include "g_messages.h"
#include "g_fastpost.h"
#include "settingswidget.h"
#include "consts.h"

Board::Board(QApplication *a)
{
//    window = new QMainWindow;
    app = a;

    globLineGadget = new G_GlobalLine;
    messagesGadget = new G_Messages;
    fastPostGadget = new G_FastPost;
    settingsWidget = new SettingsWidget;

    trayIcon = new QSystemTrayIcon(QIcon(":/images/logo_small.png"));
    trayIcon->setToolTip("Joly");
    trayIcon->setContextMenu(createMenuForTrayIcon());
    trayIcon->show();

    QObject::connect(settingsWidget, SIGNAL(valueChanged(QString,QString,QVariant)), globLineGadget, SLOT(valueChanged(QString,QString,QVariant)));
    QObject::connect(settingsWidget, SIGNAL(valueChanged(QString,QString,QVariant)), messagesGadget, SLOT(valueChanged(QString,QString,QVariant)));
    QObject::connect(settingsWidget, SIGNAL(valueChanged(QString,QString,QVariant)), fastPostGadget, SLOT(valueChanged(QString,QString,QVariant)));
    QObject::connect(settingsWidget, SIGNAL(valueChanged(QString,QString,QVariant)), SLOT(valueChanged(QString,QString,QVariant)));
}

Board::~Board()
{
    globLineGadget->deleteLater();
    messagesGadget->deleteLater();
    fastPostGadget->deleteLater();
//    window->deleteLater();
}

void Board::show() {
    Qt::WindowFlags flags = Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint;
    globLineGadget->setWindowIcon(QIcon(":/images/logo_small.png"));
    globLineGadget->setWindowFlags(flags);
    globLineGadget->show();

    messagesGadget->setWindowIcon(QIcon(":/images/logo_small.png"));
    messagesGadget->setWindowFlags(flags);
    messagesGadget->show();

    fastPostGadget->setWindowIcon(QIcon(":/images/logo_small.png"));
    fastPostGadget->setWindowFlags(flags);
    fastPostGadget->show();
}

QMenu* Board::createMenuForTrayIcon() {
    QAction *settingsAction = new QAction(tr("Открыть настройки", "Пункт в контекстном меню Tray Icon"), this);
    connect(settingsAction, SIGNAL(triggered()), settingsWidget, SLOT(show()));
    QAction *exitAction = new QAction(tr("Выйти", "Пункт в контекстном меню Tray Icon"), this);
    connect(exitAction, SIGNAL(triggered()), app, SLOT(quit()));

    QMenu *menu = new QMenu;
    menu->addAction(settingsAction);
    menu->addAction(exitAction);

    return menu;
}

void Board::valueChanged(const QString &gadget, const QString &valueName, const QVariant &value) {
    if (gadget != "system" && gadget != "all")
        return;

    if (valueName == "css") {
        app->setStyleSheet(value.toString());
    }
}


