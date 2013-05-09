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

#ifndef APITWIAUTH_TWITTERPINWIDGET_H
#define APITWIAUTH_TWITTERPINWIDGET_H

#include "ui_apitwiauth_twitterpinwidget.h"

/**
 * @brief The TwitterPinWidget class is dialog of entering Twitter authrisation PIN.
 */
class TwitterPinWidget : public QWidget, private Ui::TwitterPinWidget
{
    Q_OBJECT
    
public:
    explicit TwitterPinWidget(QWidget *parent = 0);
//    inline QString getPin() {
//        return pin;
//    }

signals:
    void openLinkAsked();
    void pinEntered(QString pin);
    void pinCancelled();

private slots:
    void on_openLinkButton_clicked();
    void on_pinLineEdit_textChanged(const QString &arg1);

    void okButtonClicked();
    void cancelButtonClicked();

private:
    QString pin;
};

#endif // APITWIAUTH_TWITTERPINWIDGET_H
