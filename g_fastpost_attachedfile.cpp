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

#include "g_fastpost_attachedfile.h"
#include <QtWidgets>

AttachedFile::AttachedFile(QString filePath, uint id, QWidget *parent) :
    QWidget(parent), m_filePath(filePath), m_id(id), m_isWaitingForRestore(false)
{
    setupUi();
}

// it builds UI of widget
void AttachedFile::setupUi(bool recreate) {

    if (recreate || !ui.icon) {
        if (!ui.icon) ui.icon = new FileIcon(sideSize);

        try {
            ui.icon->setContentFromFile(m_filePath);
        }

        catch (FileIcon::FileDoesntExist) {
            ui.icon->deleteLater();
            if (ui.text) ui.text->deleteLater();
            if (ui.removeButton) ui.removeButton->deleteLater();

            throw;
        }

        ui.icon->setBorder("1px solid #222");
    }

    if (recreate || !ui.text) {
        if (!ui.text) ui.text = new QLabel;

        QFileInfo fileInfo(m_filePath);
        ui.text->setText(fileInfo.fileName());
    }

    if (recreate || !ui.removeButton) {
        if (!ui.removeButton) {
            ui.removeButton = new QPushButton(QIcon(":/images/remove_item_transparent.png"), QString());

            ui.removeButton->setFixedSize(20, 20);
            ui.removeButton->setToolTip(tr("Удалить", "Remove attached file in FastPost Gadget"));
            connect(ui.removeButton, SIGNAL(clicked()), SLOT(waitForRestore()));
        }
        // no stuff for "recreate"
    }

    if (recreate || !ui.restoreButton) {
        if (!ui.restoreButton) {
            ui.restoreButton = new QPushButton(QIcon(":/images/restore_item_transparent.png"), QString());

            ui.restoreButton->setFixedSize(20, 20);
            ui.restoreButton->setToolTip(tr("Восстановить", "Restore attached file in FastPost Gadget"));
            connect(ui.restoreButton, SIGNAL(clicked()), SLOT(restore()));
        }
        // no stuff for "recreate"
    }

    // creating ui
    if (!this->layout()) {
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(ui.icon);
        layout->addWidget(ui.text);
        layout->addStretch();
        layout->addWidget(ui.removeButton);
        layout->addWidget(ui.restoreButton);
        ui.restoreButton->hide();

        layout->setContentsMargins(3, 3, 3, 3);
        this->setLayout(layout);
    }
}

// it sets background color to Consts::Color::lightGrey
// and changes cursor shape to Qt::PointingHandCursor
void AttachedFile::enterEvent(QEvent *event) {
    Q_UNUSED(event);
    setBackgroundColor(Consts::Colors::lighterGrey);
    setCursor(Qt::PointingHandCursor);
}

// it restores background color and cursor shape
void AttachedFile::leaveEvent(QEvent *event) {
    Q_UNUSED(event);
    restoreBackgroundColor();
    unsetCursor();
}

// it sets background color to Consts::Color::jollyTwiceLighter
void AttachedFile::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    setBackgroundColor(Consts::Colors::jollyTwiceLighter);
}

// it restores background color, cursor shape
// and sends signal about removing
void AttachedFile::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    unsetCursor();
    restoreBackgroundColor();
    waitForRestore();
}

// it sets background color of this widget and of ui.text to "color"
void AttachedFile::setBackgroundColor(QString color) {
    // do not use setStyleSheet ("background-color: " + color)
    // it fills only some parts of (not whole) widget
    setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(color));
    setPalette(pal);

    // setting palette doesn't work for QLabel
    QString css = "background-color: " + color + "; " + getStyleSheetForRightColor();
    ui.text->setStyleSheet(css);
}

// it restores default background color of this widget and ui.text
void AttachedFile::restoreBackgroundColor() {
    setAutoFillBackground(false);
    ui.text->setStyleSheet(getStyleSheetForRightColor());
}

// it sets color of ui.text to grey, replaces removeButton with restoreButton
// and starts timer to run "remove()" for 5 seconds
void AttachedFile::waitForRestore() {
    m_isWaitingForRestore = true;

    ui.text->setStyleSheet("color: " + Consts::Colors::grey);
    ui.removeButton->hide();
    ui.restoreButton->show();

    m_restoreTimer.setSingleShot(true);
    connect(&m_restoreTimer, SIGNAL(timeout()), SLOT(remove()));
    m_restoreTimer.start(10000);

    // running this because we must set right CSS for ui.text (right background color)
    enterEvent(nullptr);
}

// it stops timer started in "waitForRestore" and restores colors and butons
void AttachedFile::restore() {
    m_isWaitingForRestore = false;

    m_restoreTimer.stop();

    ui.text->setStyleSheet("");
    ui.restoreButton->hide();
    ui.removeButton->show();

    // running this because we must set right CSS for ui.text (right background color)
    enterEvent(nullptr);
}


