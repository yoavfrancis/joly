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

#ifndef G_ABSTRACTGADGET_H
#define G_ABSTRACTGADGET_H

#include <QFrame>
#include "notifierbox.h"

class G_AbstractGadget : public QFrame
{
    Q_OBJECT
public:
    explicit G_AbstractGadget (QWidget* parent = 0);
    inline QString getGadgetName() const { return m_gadgetName; }

    void show();
    inline void setGadgetName(QString gadgetName)
    {
        m_gadgetName = gadgetName;
    }

signals:
    void gadgetActivated (G_AbstractGadget*);

public slots:
    virtual void valueChanged(const QString &gadget, const QString &valueName, const QVariant &value) = 0;
    virtual void protocolUsed(const QString &gadget, const QString &action, const QVariantMap &parameters) = 0;

protected:
    // Events, used for moving gadgets by mouse
    void mousePressEvent     (QMouseEvent *);
    void mouseMoveEvent      (QMouseEvent *);
    void mouseReleaseEvent   (QMouseEvent *);

private:
    bool m_mouseMoving;
    QPoint m_lastPoint;
    QString m_gadgetName;
    bool m_headerExists;

    mutable NotifierBox box;
};

#endif // G_ABSTRACTGADGET_H
