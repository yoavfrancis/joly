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

#ifndef G_FASTPOST_H
#define G_FASTPOST_H

#include <QPointer>
#include <QStateMachine>
#include "ui_g_fastpost.h"
#include "g_abstractgadget.h"
#include "consts.h"


#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

class ApiVK;
class ApiTwi;

class G_FastPost : public G_AbstractGadget, private Ui::G_FastPost
{
    Q_OBJECT

public:
    explicit G_FastPost(QWidget *parent = 0);

public slots:
    void sendPost();
    void valueChanged(const QString &gadget, const QString &valueName, const QVariant &value);
    void protocolUsed(const QString &gadget, const QString &action, const QVariantMap &parameters);

protected:
    void setupInterface();
    void setupSocialNetworks();

#ifdef WIN_OLD_COMPILER
    enum AuthStates { unknown = -1, fail, ok };
#else
    enum class AuthStates { unknown = -1, fail, ok };
#endif

    void closeEvent(QCloseEvent *);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
    void setTimerToRestoreSNButtonsColor();
    void clear();

private slots:
    void readSettings();
    void writeSettings();
    /* Ui */
    void toggleButtons();
    void restoreSNButtonsColor();
    void setShownDropField(bool shown);
    void setSizeHintSize();
    void setUiAccordingToPostResult(const QString &socNetworkName, bool posted);

    /* Social Networks */
    // Common
    void init(const QString &socialNetwork);
    void updateState(const QString &socialNetwork);
    void postSucceed(const QString &socialNetwork);
    void postFailed(const QString &socialNetwork);
    // VK
    void init_VK();
    void updateState_VK(int networkInterfaceErrorCode = 0, QString networkInterfaceErrorDescription = "");
    void postSucceed_VK();
    void postFailed_VK();
    inline void authSucceed_VK() {
        m_authorised[Consts::SocNetworks::VK::name] = AuthStates::ok;
    }
    inline void authFailed_VK() {
        m_authorised[Consts::SocNetworks::VK::name] = AuthStates::fail;
    }
    // Twitter
    void init_Twi();
    void updateState_Twi();
    void postSucceed_Twi();
    void postFailed_Twi();
    inline void authSucceed_Twi() {
        m_authorised[Consts::SocNetworks::Twitter::name] = AuthStates::ok;
    }
    inline void authFailed_Twi() {
        m_authorised[Consts::SocNetworks::Twitter::name] = AuthStates::fail;
    }
    inline void saveConfiguration_Twi(QVariantMap config) {
        m_configuration_Twi.rawConfiguration = config;
        m_configuration_Twi.shortUrlLength = m_configuration_Twi.rawConfiguration.value("short_url_length").toInt();
        m_configuration_Twi.shortUrlLengthHttps = m_configuration_Twi.rawConfiguration.value("short_url_length_https").toInt();
    }

    void savePostState();
    void restorePostState();

    // when we're dragging text to this gadget, it sets textEdit's "accept drops" property as true
    // this function is called after end of dropping to textEdit
    // and restores defaults
    inline void setDefaultAcceptDropsPermissions() {
        setAcceptDrops(true);
        textEdit->setAcceptDrops(false);
    }

    void on_sendButton_clicked();
    void on_clearButton_clicked();
//    void on_attachButton_clicked();

    void on_useTwiSN_clicked();

private:
    enum { horisSize = 375, vertSize = 433 };

    /* Social Networks */
    QPointer<ApiVK> m_apivk;
    QPointer<ApiTwi> m_apitwi;
    QHash<QString, AuthStates> m_authorised;
    bool m_saveEnteredText;
    QStringList m_usedSocNetworks;
    QStringList m_currentlyActiveSocialNetworks;
    QList<QPixmap> m_attachedImages;

    QSize m_size;
    QStateMachine m_machine;
    struct _postState {
        QString postText;
        QStringList attachedFiles;
    } m_postState;
    QTimer m_clearTimer;

    struct _configuration_Twi {
        QVariantMap rawConfiguration;
        int shortUrlLength;
        int shortUrlLengthHttps;
        _configuration_Twi()
            : shortUrlLength(22), shortUrlLengthHttps(23) // by default
        { }
    } m_configuration_Twi;

    /* Maps */
    QMap<QString, QPushButton*> m_socNetworksButtonsMap;
};

#endif // G_FASTPOST_H
