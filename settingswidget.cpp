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

#include "settingswidget.h"
#include "consts.h"
#include <QSettings>


#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

const QString systemName = "system";

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    listWidget->addItem(titleLabel1->text().remove(QRegExp("<[^>]*>")));    // удаляем HTML-теги
    listWidget->addItem(titleLabel2->text().remove(QRegExp("<[^>]*>")));
    listWidget->addItem(titleLabel3->text().remove(QRegExp("<[^>]*>")));
    listWidget->addItem(titleLabel4->text().remove(QRegExp("<[^>]*>")));
    listWidget->addItem(titleLabel5->text().remove(QRegExp("<[^>]*>")));

    setUpMainSettingsPage();
    setUpGlobalLineSettingsPage();
    setUpMessagesSettingsPage();
    setUpFastPostSettingsPage();
    setUpDeveloperPage();
}

void SettingsWidget::setUpMainSettingsPage() {

}

void SettingsWidget::setUpGlobalLineSettingsPage() {
    QSettings settings;
    settings.beginGroup("GlobalLineGadget");
    saveHistoryCheckBox->setChecked(settings.value("saveHistory").toBool());
    saveEnteredTextInGlobalLineCheckBox->setChecked(settings.value("saveEnteredText").toBool());
    settings.endGroup();
}

void SettingsWidget::setUpMessagesSettingsPage() {
    QSettings settings;
    settings.beginGroup("MessagesGadget");
    secondsSpinBox->setValue(int(settings.value("updateInterval").toInt()/1000));

    checkBoxVK_Messages->setText(Consts::SocNetworks::VK::name);
    checkBoxGPlus_Messages->setText(Consts::SocNetworks::GPlus::name);
    checkBoxGMail_Messages->setText(Consts::SocNetworks::GMail::name);
    checkBoxGReader_Messages->setText(Consts::SocNetworks::GReader::name);
    checkBoxFB_Messages->setText(Consts::SocNetworks::Facebook::name);
    checkBoxTwi_Messages->setText(Consts::SocNetworks::Twitter::name);

    m_usedSocialNetworks_Messages = settings.value("usedSocialNetworks").toStringList();
#ifdef WIN_OLD_COMPILER
    foreach (const QString & str, m_usedSocialNetworks_Messages) {
#else
    for (const QString & str : m_usedSocialNetworks_Messages) {
#endif
        if (str == Consts::SocNetworks::VK::name) checkBoxVK_Messages->setChecked(true);
        else if (str == Consts::SocNetworks::GPlus::name) checkBoxGPlus_Messages->setChecked(true);
        else if (str == Consts::SocNetworks::GMail::name) checkBoxGMail_Messages->setChecked(true);
        else if (str == Consts::SocNetworks::GReader::name) checkBoxGReader_Messages->setChecked(true);
        else if (str == Consts::SocNetworks::Facebook::name) checkBoxFB_Messages->setChecked(true);
        else if (str == Consts::SocNetworks::Twitter::name) checkBoxTwi_Messages->setChecked(true);
    }
//    for (QStringList::const_iterator i = m_usedSocialNetworks_Messages.constBegin(); i != m_usedSocialNetworks_Messages.constEnd(); ++i) {

//    }

    settings.endGroup();
}

void SettingsWidget::setUpFastPostSettingsPage() {
    QSettings settings;
    settings.beginGroup("FastPostGadget");
//    bool value = settings.value("saveEnteredText").toBool();
//    qDebug() << value;
    saveEnteredTextInFastPostCheckBox->setChecked(settings.value("saveEnteredText").toBool());

    checkBoxVK_FastPost->setText(Consts::SocNetworks::VK::name);
    checkBoxGPlus_FastPost->setText(Consts::SocNetworks::GPlus::name);
    checkBoxFB_FastPost->setText(Consts::SocNetworks::Facebook::name);
    checkBoxTwi_FastPost->setText(Consts::SocNetworks::Twitter::name);

    m_usedSocialNetworks_FastPost = settings.value("usedSocialNetworks").toStringList();
    forc11 (const QString & str, m_usedSocialNetworks_FastPost) {
        if (str == Consts::SocNetworks::VK::name) checkBoxVK_FastPost->setChecked(true);
        else if (str == Consts::SocNetworks::GPlus::name) checkBoxGPlus_FastPost->setChecked(true);
        else if (str == Consts::SocNetworks::Facebook::name) checkBoxFB_FastPost->setChecked(true);
        else if (str == Consts::SocNetworks::Twitter::name) checkBoxTwi_FastPost->setChecked(true);
    }
    settings.endGroup();
}

void SettingsWidget::setUpDeveloperPage() {
    m_css = Consts::css;
    cssTextEdit->setPlainText(m_css);
}

void SettingsWidget::updateUsedSocialNetworksList_Messages() {
    m_usedSocialNetworks_Messages.clear();
    if (checkBoxVK_Messages->isChecked())
        m_usedSocialNetworks_Messages << Consts::SocNetworks::VK::name;
    if (checkBoxGPlus_Messages->isChecked())
        m_usedSocialNetworks_Messages << Consts::SocNetworks::GPlus::name;
    if (checkBoxGMail_Messages->isChecked())
        m_usedSocialNetworks_Messages << Consts::SocNetworks::GMail::name;
    if (checkBoxGReader_Messages->isChecked())
        m_usedSocialNetworks_Messages << Consts::SocNetworks::GReader::name;
    if (checkBoxFB_Messages->isChecked())
        m_usedSocialNetworks_Messages << Consts::SocNetworks::Facebook::name;
    if (checkBoxTwi_Messages->isChecked())
        m_usedSocialNetworks_Messages << Consts::SocNetworks::Twitter::name;
}

void SettingsWidget::updateUsedSocialNetworksList_FastPost() {
    m_usedSocialNetworks_FastPost.clear();
    if (checkBoxVK_FastPost->isChecked())
        m_usedSocialNetworks_FastPost << Consts::SocNetworks::VK::name;
    if (checkBoxGPlus_FastPost->isChecked())
        m_usedSocialNetworks_FastPost << Consts::SocNetworks::GPlus::name;
    if (checkBoxFB_FastPost->isChecked())
        m_usedSocialNetworks_FastPost << Consts::SocNetworks::Facebook::name;
    if (checkBoxTwi_FastPost->isChecked())
        m_usedSocialNetworks_FastPost << Consts::SocNetworks::Twitter::name;
}

void SettingsWidget::on_saveEnteredTextInGlobalLineCheckBox_stateChanged(int /*arg1*/) {
    emit valueChanged(Consts::Gadgets::GlobalLine::name, "saveEnteredText", saveEnteredTextInGlobalLineCheckBox->isChecked());
}

void SettingsWidget::on_checkBoxVK_Messages_stateChanged(int /*arg1*/) {
    updateUsedSocialNetworksList_Messages();
    emit valueChanged(Consts::Gadgets::Messages::name, "usedSocialNetworks", m_usedSocialNetworks_Messages);
}

void SettingsWidget::on_checkBoxGPlus_Messages_stateChanged(int /*arg1*/) {
    updateUsedSocialNetworksList_Messages();
    emit valueChanged(Consts::Gadgets::Messages::name, "usedSocialNetworks", m_usedSocialNetworks_Messages);
}

void SettingsWidget::on_checkBoxGMail_Messages_stateChanged(int /*arg1*/) {
    updateUsedSocialNetworksList_Messages();
    emit valueChanged(Consts::Gadgets::Messages::name, "usedSocialNetworks", m_usedSocialNetworks_Messages);
}

void SettingsWidget::on_checkBoxGReader_Messages_stateChanged(int /*arg1*/) {
    updateUsedSocialNetworksList_Messages();
    emit valueChanged(Consts::Gadgets::Messages::name, "usedSocialNetworks", m_usedSocialNetworks_Messages);
}

void SettingsWidget::on_checkBoxFB_Messages_stateChanged(int /*arg1*/) {
    updateUsedSocialNetworksList_Messages();
    emit valueChanged(Consts::Gadgets::Messages::name, "usedSocialNetworks", m_usedSocialNetworks_Messages);
}

void SettingsWidget::on_checkBoxTwi_Messages_stateChanged(int /*arg1*/) {
    updateUsedSocialNetworksList_Messages();
    emit valueChanged(Consts::Gadgets::Messages::name, "usedSocialNetworks", m_usedSocialNetworks_Messages);
}

void SettingsWidget::on_saveEnteredTextInFastPostCheckBox_stateChanged(int /*arg1*/) {
    emit valueChanged(Consts::Gadgets::FastPost::name, "saveEnteredText", saveEnteredTextInFastPostCheckBox->isChecked());
}

void SettingsWidget::on_checkBoxGPlus_FastPost_stateChanged(int arg1) {
    Q_UNUSED(arg1);

    updateUsedSocialNetworksList_FastPost();
    emit valueChanged(Consts::Gadgets::FastPost::name, "usedSocialNetworks", m_usedSocialNetworks_FastPost);
}

void SettingsWidget::on_checkBoxFB_FastPost_stateChanged(int arg1) {
    Q_UNUSED(arg1);

    updateUsedSocialNetworksList_FastPost();
    emit valueChanged(Consts::Gadgets::FastPost::name, "usedSocialNetworks", m_usedSocialNetworks_FastPost);
}

void SettingsWidget::on_checkBoxTwi_FastPost_stateChanged(int arg1) {
    Q_UNUSED(arg1);

    updateUsedSocialNetworksList_FastPost();
    emit valueChanged(Consts::Gadgets::FastPost::name, "usedSocialNetworks", m_usedSocialNetworks_FastPost);
}

void SettingsWidget::on_checkBoxVK_FastPost_stateChanged(int arg1) {
    Q_UNUSED(arg1);

    updateUsedSocialNetworksList_FastPost();
    emit valueChanged(Consts::Gadgets::FastPost::name, "usedSocialNetworks", m_usedSocialNetworks_FastPost);
}

void SettingsWidget::on_setButton_clicked() {
    m_css = cssTextEdit->toPlainText();
    emit valueChanged(systemName, "css", m_css);
}


void SettingsWidget::on_resetButton_clicked() {
    cssTextEdit->setPlainText(m_css);
}

void SettingsWidget::on_fullResetButton_clicked() {
    cssTextEdit->setPlainText(Consts::css);
}

void SettingsWidget::on_newLogin_VK_clicked() {
    emit valueChanged(Consts::Gadgets::FastPost::name, "newLogin", Consts::SocNetworks::VK::name);
}

void SettingsWidget::on_newLogin_Twi_clicked() {
    emit valueChanged(Consts::Gadgets::FastPost::name, "newLogin", Consts::SocNetworks::Twitter::name);
}
