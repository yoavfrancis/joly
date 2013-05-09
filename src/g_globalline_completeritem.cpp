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

#include "g_globalline_completeritem.h"
#include <QHBoxLayout>
#include "consts.h"

CompleterItem::CompleterItem(Position pos, QWidget *parent) :
    QFrame(parent), m_isFocused(false), m_pos(pos)
{
    setDefaultColors();
    setupUi();
}

CompleterItem::CompleterItem(QPixmap pixmap, QString text, Position pos, QWidget *parent) :
    QFrame(parent), m_isFocused(false), m_pos(pos)
{
    ui.pixmap = new QLabel;
    ui.text = new QLabel;
    setPixmap(pixmap);
    setText(text);

    setDefaultColors();
    setupUi();
}

CompleterItem::CompleterItem(CompleterItem::Content content, QWidget *parent) :
    QFrame(parent), m_isFocused(false), m_pos(content.pos)
{
    ui.pixmap = new QLabel;
    ui.text = new QLabel;
    setPixmap(content.pixmap);
    setText(content.text);

    setDefaultColors();
    setupUi();
}

void CompleterItem::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    setBackgroundColor(m_colors.active);
    emit clicked(getContent());
}

void CompleterItem::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    restoreBackgroundColor();
}

void CompleterItem::enterEvent(QEvent *event) {
    Q_UNUSED(event);
    setFocused(true);
}

void CompleterItem::leaveEvent(QEvent *event) {
    Q_UNUSED(event);
    restoreBackgroundColor();
    setFocused(false);
}

void CompleterItem::restoreBackgroundColor() {
    if (m_isFocused)
        setBackgroundColor(m_colors.focus);
    else
        setBackgroundColor(m_colors.basic);
}

void CompleterItem::setupUi() {
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(ui.pixmap);
    layout->addWidget(ui.text);
    layout->addStretch();
    layout->setContentsMargins(0, 5, 0, 5);
    ui.text->setTextFormat(Qt::RichText);
    setLayout(layout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setBackgroundColor(m_colors.basic);
}

void CompleterItem::setDefaultColors() {
    m_colors.basic = QColor("white");
    m_colors.hover = QColor(Consts::Colors::lightestGrey);
    m_colors.focus = QColor(Consts::Colors::jollyLightest);
    m_colors.active = QColor(Consts::Colors::jolly);
}

void CompleterItem::setBackgroundColor(QColor color) {
    setStyleSheet("background-color: " + color.name());
}
