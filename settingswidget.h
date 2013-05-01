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

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include "ui_settingswidget.h"

class SettingsWidget : public QWidget, private Ui::SettingsWidget
{
    Q_OBJECT
    
public:
    explicit SettingsWidget(QWidget *parent = 0);

signals:
    void valueChanged(const QString &gadget, const QString &valueName, const QVariant &value);

protected:
    void setUpMainSettingsPage();
    void setUpGlobalLineSettingsPage();
    void setUpMessagesSettingsPage();
    void setUpFastPostSettingsPage();
    void setUpDeveloperPage();

    void updateUsedSocialNetworksList_Messages();
    void updateUsedSocialNetworksList_FastPost();

private slots:
    void on_saveHistoryCheckBox_stateChanged(int /*arg1*/);
    void on_saveEnteredTextInGlobalLineCheckBox_stateChanged(int /*arg1*/);
    void on_secondsSpinBox_valueChanged(int arg1);

    void on_checkBoxVK_Messages_stateChanged(int /*arg1*/);
    void on_checkBoxGPlus_Messages_stateChanged(int /*arg1*/);
    void on_checkBoxGMail_Messages_stateChanged(int /*arg1*/);
    void on_checkBoxGReader_Messages_stateChanged(int /*arg1*/);
    void on_checkBoxFB_Messages_stateChanged(int /*arg1*/);
    void on_checkBoxTwi_Messages_stateChanged(int /*arg1*/);

    void on_saveEnteredTextInFastPostCheckBox_stateChanged(int /*arg1*/);

    void on_checkBoxGPlus_FastPost_stateChanged(int arg1);
    void on_checkBoxFB_FastPost_stateChanged(int arg1);
    void on_checkBoxTwi_FastPost_stateChanged(int arg1);
    void on_checkBoxVK_FastPost_stateChanged(int arg1);

    void on_setButton_clicked();

    void on_resetButton_clicked();

    void on_fullResetButton_clicked();

    void on_newLogin_VK_clicked();

    void on_newLogin_Twi_clicked();

private:
    QStringList m_usedSocialNetworks_Messages;
    QStringList m_usedSocialNetworks_FastPost;

    QString m_css;
};

#endif // SETTINGSWIDGET_H
