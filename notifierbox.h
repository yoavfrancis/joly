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

#ifndef NOTIFIERWIDGET_H
#define NOTIFIERWIDGET_H

#include "ui_notifierbox.h"

class NotifierBox : public QWidget, private Ui::NotifierWidget
{
    Q_OBJECT
    
public:
    explicit NotifierBox(QWidget *parent = 0);
    explicit NotifierBox(const QString &title, const QString &description, QWidget *parent = 0);

    inline QString title() const { return m_title; }
    inline void setTitle(const QString& title) {
        m_title = title;
        setTitleLabel(m_title);
        setWindowTitle(m_title);
    }

    inline QString description() const { return m_description; }
    inline void setDescription(const QString& description) {
        m_description = description;
        setDescriptionLabel(m_description);
    }

signals:
    void linkActivated(const QString &gadget, const QString &action, const QVariantMap &parameters);

private slots:
    void on_descriptionLabel_linkActivated(const QString &link);

private:
    inline void setTitleLabel(const QString &text) {
        titleLabel->setText("<h1>" + text + "</h1>");
    }

    inline void setDescriptionLabel(const QString &text) {
        descriptionLabel->setText(text);
    }

    void init();

    QString m_title;
    QString m_description;
};

#endif // NOTIFIERWIDGET_H
