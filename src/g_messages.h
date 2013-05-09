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

#ifndef G_MESSAGES_H
#define G_MESSAGES_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>
#include <QList>
#include <QMap>
#include <QHash>
#include "g_abstractgadget.h"
#include "consts.h"

class QWebView;
class ApiVK;
class QTimer;
class QLabel;
class QPushButton;

class G_Messages : public G_AbstractGadget
{
    Q_OBJECT

public:
    explicit G_Messages(QWidget* parent = 0);

public slots:
    void updateVKMessages();
//    void authFailed(QString, QString);

    void valueChanged(const QString &gadget, const QString &valueName, const QVariant &value);
    void protocolUsed(const QString &gadget, const QString &action, const QVariantMap &parameters);

protected:
    void closeEvent(QCloseEvent* event);

    void readSettings();
    void writeSettings();

protected slots:
    inline void openVKMessages () {
        QDesktopServices::openUrl(QUrl(Consts::SocNetworks::VK::imUrl()));
    }

    void vkInit(bool init = true);

private:
    ApiVK *m_apivk;
    int m_updateInterval;
    QHash<QString, QTimer*> m_updateTimer;

    QHash<QString, QLabel*> m_labels;
    QHash<QString, QPushButton*> m_buttons;
//    QHash<QString, QUrl> m_urls;

    QStringList m_usedSocialNetworks;

//    QString m_vkSocName;
//    QString m_gplusSocName;
//    QString m_gmailSocName;
//    QString greaderSocName;
//    QString fbSocName;
//    QString twSocName;
};

#endif // G_MESSAGES_H
