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
#include <QtDebug>
#include "g_messages.h"
#include "consts.h"
#include "apivk.h"
#include "apivkpermissions.h"

G_Messages::G_Messages(QWidget* parent) :
    G_AbstractGadget(parent), m_updateInterval(2000) {
    readSettings();
    setGadgetName("Messages Gadget");

    m_apivk = 0;
    QHBoxLayout *layout = new QHBoxLayout(this);

    for (QStringList::size_type i = 0; i < m_usedSocialNetworks.size(); ++i) {
        QPushButton *pb = new QPushButton(tr("0"));
        QLabel *lbl = new QLabel(m_usedSocialNetworks[i]);

        pb->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        pb->setMinimumSize(pb->minimumSizeHint().height(), pb->minimumSizeHint().height());

        layout->addWidget(lbl);
        layout->addWidget(pb);

        lbl->setBuddy(pb);

        m_buttons[m_usedSocialNetworks[i]] = pb;
        m_labels[m_usedSocialNetworks[i]] = lbl;
    }

    vkInit(m_usedSocialNetworks.contains(Consts::SocNetworks::VK::name));

    setLayout(layout);
    setFixedSize(sizeHint());
}

void G_Messages::vkInit(bool init) {
//    m_urls[Consts::SocNetworks::VK::name] = Consts::SocNetworks::VK::imUrl();

    if (init) {
        m_buttons[Consts::SocNetworks::VK::name]->setText("?");
        if (!m_apivk) m_apivk = new ApiVK(this);

        connect(m_apivk, SIGNAL(authorisationSucceed()), m_apivk, SLOT(getUnreadMessagesVariationRequest()));
        connect(m_apivk, SIGNAL(requestFinished()), this, SLOT(updateVKMessages()));

        connect(m_buttons[Consts::SocNetworks::VK::name], SIGNAL(clicked()), this, SLOT(openVKMessages()));

        m_apivk->authorise();
    }
}

void G_Messages::updateVKMessages() {
    int errorCode = 0;
    int msgsChange = m_apivk->getUnreadMessagesVariation(&errorCode);

    if (errorCode) {
        qDebug() << "G_Messages: ApiVK::getUnreadMessages() returned error code" << errorCode;
        if (errorCode == ApiVK::ServerError) {
            qDebug() << "Server returned error:" << m_apivk->getServerErrorCode() << m_apivk->getServerErrorDescription();
        }
    }

    int actualMessagesCount = m_buttons[Consts::SocNetworks::VK::name]->text().toInt() + msgsChange;
    m_buttons[Consts::SocNetworks::VK::name]->setText(QString::number(actualMessagesCount));

    m_apivk->getUnreadMessagesVariationRequest();
}

void G_Messages::valueChanged(const QString &gadget, const QString &valueName, const QVariant &value) {
    if (gadget != "Messages" && gadget != "all")
        return;

    if (valueName == "updateInterval") {
        m_updateInterval = value.toInt();
        m_updateTimer[Consts::SocNetworks::VK::name]->start(m_updateInterval);
    }

    else if (valueName == "usedSocialNetworks") {
        m_usedSocialNetworks = value.toStringList();
    }
}

void G_Messages::protocolUsed(const QString &gadget, const QString &action, const QVariantMap &parameters) {
    Q_UNUSED(gadget);
    Q_UNUSED(action);
    Q_UNUSED(parameters);
}

void G_Messages::readSettings() {
    QSettings settings;
    settings.beginGroup("MessagesGadget");

    restoreGeometry(settings.value("geometry").toByteArray());
    m_updateInterval = settings.value("updateInterval", QVariant(2000)).toInt();
    m_usedSocialNetworks = settings.value("usedSocialNetworks", QVariant(QStringList() << Consts::SocNetworks::VK::name)).toStringList();

    settings.endGroup();

    writeSettings();
}

void G_Messages::writeSettings() {
    QSettings settings;
    settings.beginGroup("MessagesGadget");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("updateInterval", m_updateInterval);
    settings.setValue("usedSocialNetworks", m_usedSocialNetworks);

    settings.endGroup();

}

void G_Messages::closeEvent(QCloseEvent* /*event*/) {
    writeSettings();
    m_apivk->deleteLater();
}
