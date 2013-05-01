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

#include "apitwiauth_twitterpinwidget.h"
#include <QtWidgets>

TwitterPinWidget::TwitterPinWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    openLinkButton->setFixedSize(pinLineEdit->size());
    pinLineEdit->hide();

    pinLineEdit->setValidator(new QRegExpValidator(QRegExp("\\d{7}")));
}

void TwitterPinWidget::on_openLinkButton_clicked() {
    emit openLinkAsked();
    openLinkButton->hide();
    pinLineEdit->show();
}

void TwitterPinWidget::on_pinLineEdit_textChanged(const QString &arg1) {
    Q_UNUSED(arg1);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    if (pinLineEdit->hasAcceptableInput())
        okButton->setEnabled(true);
    else
        okButton->setEnabled(false);
}

void TwitterPinWidget::okButtonClicked() {
    emit pinEntered(pinLineEdit->text());
    close();
}

void TwitterPinWidget::cancelButtonClicked() {
    emit pinCancelled();
    close();
}
