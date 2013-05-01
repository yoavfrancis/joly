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
#include "g_abstractgadget.h"

G_AbstractGadget::G_AbstractGadget(QWidget* parent) :
    QFrame (parent), m_mouseMoving(false), m_headerExists(false)
{
    connect(&box, SIGNAL(linkActivated(QString,QString,QVariantMap)), SLOT(protocolUsed(QString,QString,QVariantMap)));
}

void G_AbstractGadget::show() {
    setWindowTitle(m_gadgetName);
    setFixedHeight(sizeHint().height());
    QFrame::show();
}

void G_AbstractGadget::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        m_lastPoint = event->pos();
        m_mouseMoving = true;
#ifdef Q_OS_LINUX
        setCursor(Qt::SizeAllCursor);
#else
        setCursor(Qt::ClosedHandCursor);
#endif
    }
}

void G_AbstractGadget::mouseMoveEvent(QMouseEvent *event) {
    if((event->buttons() == Qt::LeftButton) && m_mouseMoving)
        this->move(event->globalX()-m_lastPoint.x(),
                   event->globalY()-m_lastPoint.y());
}

void G_AbstractGadget::mouseReleaseEvent(QMouseEvent *event) {
    if ((event->button() == Qt::LeftButton) && m_mouseMoving) {
        m_mouseMoving = false;
        unsetCursor();
    }
}
