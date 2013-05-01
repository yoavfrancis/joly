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

#include "g_fastpost.h"
#include "apivk.h"
#include "apivkpermissions.h"
#include "apitwi.h"
#include "strtools.h"
#include "consts.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QSettings>
#include <QShortcut>
#include <QState>
#include <QPropertyAnimation>
#include "g_fastpost_attachedfile.h"


#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

const ApiVKPermissions vkPermissions = ApiVKPermissions::wall | ApiVKPermissions::photos;

////////////////////////////////////SETUPS//////////////////////////////////////
G_FastPost::G_FastPost(QWidget *parent) :
    G_AbstractGadget (parent)
{
    setupUi(this);
    readSettings();
    setGadgetName("FastPost Gadget");

    // Setting maps
    {
        using namespace Consts::SocNetworks;
        m_socNetworksButtonsMap[VK::name] = useVkSN;
        m_socNetworksButtonsMap[Twitter::name] = useTwiSN;
        m_socNetworksButtonsMap[Facebook::name] = nullptr;
        m_socNetworksButtonsMap[GPlus::name] = nullptr;
    }

    // Interface
    setupInterface();

    // Setting defaults
    setDefaultAcceptDropsPermissions();

    // Social Networks
    setupSocialNetworks();

    // Calling it after performing ALL operations to set truly correct size
    setSizeHintSize();
}

void G_FastPost::setupInterface() {
    toggleButtons();

    dropField->hide();
    attachedFilesField->hide();

    textEdit->setAcceptRichText(false);
    connect(textEdit, SIGNAL(textChanged()), SLOT(toggleButtons()));
    connect(textEdit, SIGNAL(droppingFinished()), SLOT(setDefaultAcceptDropsPermissions()));
    connect(attachedFilesField, SIGNAL(becomedEmpty()), SLOT(toggleButtons()));
    connect(attachedFilesField, SIGNAL(becomedNotEmpty()), SLOT(toggleButtons()));
    connect(attachedFilesField, SIGNAL(fileRemoved()), SLOT(setSizeHintSize()));

    // setting shortcuts to post
    QShortcut *shortcut1 = new QShortcut(Qt::CTRL + Qt::Key_Enter, this);
    connect(shortcut1, SIGNAL(activated()), sendButton, SLOT(click()));

    QShortcut *shortcut2 = new QShortcut(Qt::CTRL + Qt::Key_Return, this);
    connect(shortcut2, SIGNAL(activated()), sendButton, SLOT(click()));
}

void G_FastPost::setupSocialNetworks() {
    useVkSN->hide();
    useTwiSN->hide();

    // Showing buttons of used social netwotks
    forc11 (const QString &socName, m_usedSocNetworks) {
        m_authorised[socName] = AuthStates::unknown;
        init(socName);

        m_socNetworksButtonsMap[socName]->setText(socName);
        m_socNetworksButtonsMap[socName]->show();
        connect(m_socNetworksButtonsMap[socName], SIGNAL(toggled(bool)), SLOT(toggleButtons()));
    }

    // If we have only one active social network, we activate it's button
    if (m_usedSocNetworks.length() == 1) {
        QString activeSocNetwork = m_usedSocNetworks.first();

        m_socNetworksButtonsMap[activeSocNetwork]->setChecked(true);
    }
}

//////////////////////////////////////BASICS//////////////////////////////////
void G_FastPost::sendPost() {
    if (useVkSN->isChecked())
        m_apivk->post(textEdit->toPlainText(), attachedFilesField->getFilesList());

    if (useTwiSN->isChecked())
        m_apitwi->post(textEdit->toPlainText());
    // other SN
}

void G_FastPost::toggleButtons() {
    bool thereIsText = !textEdit->toPlainText().simplified().isEmpty();
    bool thereAreFiles = !attachedFilesField->isEmpty();
    bool thereAreEnabledSocNetworks = false;
    for (auto iter = m_socNetworksButtonsMap.constBegin(); iter != m_socNetworksButtonsMap.constEnd(); ++iter) {
        if (iter.value() == nullptr) continue;
        thereAreEnabledSocNetworks = thereAreEnabledSocNetworks || iter.value()->isChecked();
    }

    bool buttonsCanBeEnabled = (thereIsText || thereAreFiles) && thereAreEnabledSocNetworks;
    sendButton->setEnabled(buttonsCanBeEnabled);
    clearButton->setEnabled(buttonsCanBeEnabled);

    // Calculating and writing leftover tweet length
    if (useTwiSN->isChecked() && !(textEdit->toPlainText().isEmpty())) {
        // Calculating tweet length
        QString text = textEdit->toPlainText();

        // Magic
        QRegExp httpRegEx = QRegExp("(http):\\/\\/(?:[\\w\\.\\-\\+]+:{0,1}[\\w\\.\\-\\+]*@)?(?:[a-z0-9\\-\\.]+)(?::[0-9]+)?(?:\\/|\\/(?:[\\w#!:\\.\\?\\+=&%@!\\-\\/\\(\\)]+)|\\?(?:[\\w#!:\\.\\?\\+=&%@!\\-\\/\\(\\)]+))?");
        QRegExp httpsRegEx = QRegExp("(https):\\/\\/(?:[\\w\\.\\-\\+]+:{0,1}[\\w\\.\\-\\+]*@)?(?:[a-z0-9\\-\\.]+)(?::[0-9]+)?(?:\\/|\\/(?:[\\w#!:\\.\\?\\+=&%@!\\-\\/\\(\\)]+)|\\?(?:[\\w#!:\\.\\?\\+=&%@!\\-\\/\\(\\)]+))?");

        int httpCount = text.count(httpRegEx);
        int httpsCount = text.count(httpsRegEx);

        text.remove(httpRegEx).remove(httpsRegEx);
        int textLength = text.length() + httpCount * m_configuration_Twi.shortUrlLength + httpsCount * m_configuration_Twi.shortUrlLengthHttps;

        if (!m_attachedImages.isEmpty())
            textLength += m_configuration_Twi.shortUrlLengthHttps;

        const int twitterStatusLength = 140;
        int allowedSymbols = twitterStatusLength - textLength;
        if (allowedSymbols >= 0) {
            statusLabel->setText(QString::number(allowedSymbols));
            sendButton->setEnabled(true);
        } else {
            statusLabel->setText("<font color=\"red\">" + QString::number(allowedSymbols) + "</font>");
            sendButton->setEnabled(false);
        }
    } else {
        statusLabel->clear();
    }
}

// it sets basic size of gadget: sizeHint()
void G_FastPost::setSizeHintSize() {
    setFixedSize(sizeHint());
}

void G_FastPost::clear() {
    textEdit->clear();
    textEdit->setEnabled(true);

    attachedFilesField->clear();
    statusLabel->clear();

    setSizeHintSize();
    toggleButtons();
}




///////////////////////////////////SOCIAL NETWORKS///////////////////////////////////////////
void G_FastPost::init(const QString &socialNetwork) {
    if (socialNetwork == Consts::SocNetworks::VK::name)
        init_VK();

    else if (socialNetwork == Consts::SocNetworks::Twitter::name)
        init_Twi();
}

void G_FastPost::updateState(const QString &socialNetwork) {
    if (socialNetwork == Consts::SocNetworks::VK::name)
        updateState_VK();

    else if (socialNetwork == Consts::SocNetworks::Twitter::name)
        updateState_Twi();
}

void G_FastPost::postSucceed(const QString &socialNetwork) {
    if (socialNetwork == Consts::SocNetworks::VK::name)
        postSucceed_VK();

    else if (socialNetwork == Consts::SocNetworks::Twitter::name)
        postSucceed_Twi();
}

void G_FastPost::postFailed(const QString &socialNetwork) {
    if (socialNetwork == Consts::SocNetworks::VK::name)
        postFailed_VK();

    else if (socialNetwork == Consts::SocNetworks::Twitter::name)
        postFailed_Twi();
}


void G_FastPost::setUiAccordingToPostResult(const QString &socNetworkName, bool posted) {
    QString styleSheet = QString("background-color: ") + (posted ? "green" : "red");
    m_socNetworksButtonsMap[socNetworkName]->setStyleSheet(styleSheet);
    statusLabel->clear();

    static bool prevendFromClearing = false;

    if (posted) {
        if (!prevendFromClearing) clear();
    } else {
        sendButton->setEnabled(true);
        textEdit->setEnabled(true);
        if (textEdit->toPlainText().isEmpty() && attachedFilesField->isEmpty())
            restorePostState();
        prevendFromClearing = true;
    }

    setTimerToRestoreSNButtonsColor();
}

void G_FastPost::setTimerToRestoreSNButtonsColor() {
    m_clearTimer.setSingleShot(true);
    connect(&m_clearTimer, SIGNAL(timeout()), SLOT(restoreSNButtonsColor()));
    m_clearTimer.start(5000); // 5 seconds
}

void G_FastPost::restoreSNButtonsColor() {
    forc11 (QString str, m_usedSocNetworks)
        m_socNetworksButtonsMap[str]->setStyleSheet("");
}

void G_FastPost::savePostState() {
    m_postState.postText = textEdit->toPlainText();
    m_postState.attachedFiles = attachedFilesField->getFilesList();
}

void G_FastPost::restorePostState() {
    textEdit->setText(m_postState.postText);
    attachedFilesField->setFilesList(m_postState.attachedFiles);
}

////////////////////////////////////VK//////////////////////////////////////
void G_FastPost::init_VK() {
    m_apivk = new ApiVK;

    connect(m_apivk, SIGNAL(authorisationSucceed()), this, SLOT(authSucceed_VK()));
    connect(m_apivk, SIGNAL(authorisationFailed(QString, QString)), this, SLOT(authFailed_VK()));
    connect(m_apivk, SIGNAL(requestFinished()), this, SLOT(updateState_VK()));
    connect(m_apivk, SIGNAL(requestFailed(int,QString)), this, SLOT(updateState_VK(int,QString)));

    m_apivk->authorise();
}

void G_FastPost::updateState_VK(int networkInterfaceErrorCode, QString networkInterfaceErrorDescription) {
    int insideErrorCode = m_apivk->postResult();
        // insideErrorStatus == 0, when everything is OK, otherwise it's errorCode

    if (!networkInterfaceErrorCode && !insideErrorCode) {
        postSucceed_VK();
    } else {
        qDebug() << "G_FastPost:" << insideErrorCode << insideErrorCode << networkInterfaceErrorCode << networkInterfaceErrorDescription << "; ApiVk say:"
                 << m_apivk->getServerErrorCode() << m_apivk->getServerErrorDescription();
        postFailed_VK();
    }
}

void G_FastPost::postSucceed_VK() {
    setUiAccordingToPostResult(Consts::SocNetworks::VK::name, true);
}

void G_FastPost::postFailed_VK() {
    setUiAccordingToPostResult(Consts::SocNetworks::VK::name, false);
}

////////////////////////////////////Twitter//////////////////////////////////////
void G_FastPost::init_Twi() {
    m_apitwi = new ApiTwi;

    connect(m_apitwi, SIGNAL(authorisationSucceed()), this, SLOT(authSucceed_Twi()));
    connect(m_apitwi, SIGNAL(authorisationFailed()), this, SLOT(authFailed_Twi()));
    connect(m_apitwi, SIGNAL(requestFinished()), this, SLOT(updateState_Twi()));
    connect(m_apitwi, SIGNAL(requestFailed()), this, SLOT(postFailed_Twi()));

    connect(m_apitwi, SIGNAL(configurationIsReady(QVariantMap)), SLOT(saveConfiguration_Twi(QVariantMap)));

    m_apitwi->authorise();
}

void G_FastPost::updateState_Twi() {
    int result = m_apitwi->postResult();
    if (result == 0) {
        postSucceed_Twi();
    } else {
        postFailed_Twi();
    }
}

void G_FastPost::postSucceed_Twi() {
    setUiAccordingToPostResult(Consts::SocNetworks::Twitter::name, true);
}

void G_FastPost::postFailed_Twi() {
    setUiAccordingToPostResult(Consts::SocNetworks::Twitter::name, false);
}


////////////////////////////////////SLOTS//////////////////////////////////////
void G_FastPost::valueChanged(const QString &gadget, const QString &valueName, const QVariant &value) {
    if (gadget != "FastPost" && gadget != "all")
        return;

    if (valueName == "saveEnteredText") {
        m_saveEnteredText = value.toBool();
    }

    else if (valueName == "usedSocialNetworks") {
        m_usedSocNetworks = value.toStringList();
    }

    else if (valueName == "newLogin") {
        if (value.toString() == Consts::SocNetworks::VK::name)
            m_apivk->newAuthoriseRequest();

        else if (value.toString() == Consts::SocNetworks::Twitter::name)
            m_apitwi->newAuthoriseRequest();
    }

    writeSettings();
}

void G_FastPost::protocolUsed(const QString &gadget, const QString &action, const QVariantMap &parameters) {
    Q_UNUSED(gadget);
    Q_UNUSED(action);
    Q_UNUSED(parameters);
}

void G_FastPost::on_sendButton_clicked() {
    bool isAuthorisedInAllUsedNetworks = true;
    forc11 (QString socNetwork, m_usedSocNetworks) {
        if (socNetwork == Consts::SocNetworks::VK::name && useVkSN->isChecked())
            isAuthorisedInAllUsedNetworks = isAuthorisedInAllUsedNetworks && m_apivk->isAuthorised();

        else if (socNetwork == Consts::SocNetworks::Twitter::name && useTwiSN->isChecked())
            isAuthorisedInAllUsedNetworks = isAuthorisedInAllUsedNetworks && m_apitwi->isAuthorised();
    }

    if (isAuthorisedInAllUsedNetworks) {
        statusLabel->setText(tr("Отправляется...", "Status in FastPost Gadget"));

        sendButton->setEnabled(false);
        textEdit->setEnabled(false);

        sendPost();
    } else {
        statusLabel->setText(tr("Вы не авторизированы", "Status in FastPost Gadget"));
    }

    savePostState();
}

void G_FastPost::on_clearButton_clicked() {
    clear();
    setSizeHintSize();
}

void G_FastPost::closeEvent(QCloseEvent *) {
    writeSettings();
}

void G_FastPost::readSettings() {
    QSettings settings;

    settings.beginGroup("FastPostGadget");
    restoreGeometry(settings.value("geometry").toByteArray());

    m_saveEnteredText = settings.value("saveEnteredText", QVariant(true)).toBool();

    if (m_saveEnteredText)
        textEdit->setText(settings.value("text").toString());

    m_usedSocNetworks = settings.value("usedSocialNetworks", QVariant(QStringList() << Consts::SocNetworks::VK::name << Consts::SocNetworks::Twitter::name)).toStringList();

    settings.endGroup();

    writeSettings();

    toggleButtons();
}

void G_FastPost::writeSettings() {
    QSettings settings;

    settings.beginGroup("FastPostGadget");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("saveEnteredText", m_saveEnteredText);
    settings.setValue("usedSocialNetworks", m_usedSocNetworks);

    if (m_saveEnteredText)
        settings.setValue("text", textEdit->toPlainText());
    else
        settings.setValue("text", QString());

    settings.endGroup();
}

//////////////////////////////////////////DRAG AND DROP///////////////////////////////////////////
// reimplements dragEnterEvent
// it accepts images
// plain text should be accepted by textEdit
void G_FastPost::dragEnterEvent(QDragEnterEvent *event) {
    // saving current state
    m_size = size();
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // if it's simple text - nothing more
    if (event->mimeData()->hasText() && !event->mimeData()->hasUrls()) {
        // we're passing control of dropping to textEdit
        setAcceptDrops(false);
        textEdit->setAcceptDrops(true);
        // when dropping to textEdit is finished, we restore defaults in restoreDefaultAcceptDrops()

        event->acceptProposedAction();
    } else {
        if (dropField->areAppropriateFiles(event->mimeData()->urls())) {
            dropField->setContentForMimeData(event->mimeData());
            event->acceptProposedAction();

            setShownDropField(true);
        }
    }
}

void G_FastPost::dragLeaveEvent(QDragLeaveEvent *event) {
    Q_UNUSED(event);
    setShownDropField(false);
    resize(m_size);
}

// it must append dropped file to attached files list,
// hide dropField and show everything else
void G_FastPost::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();

        forc11 (const QUrl &url, urls) {
#ifdef Q_OS_WIN
            QString filePath = url.toString().remove("file:///");
#else
            QString filePath = url.toString().remove("file://");
#endif
            OSTools::UserFilesInterface::FileKind fileKind = OSTools::UserFilesInterface::getFileKind(filePath);

            if (fileKind == OSTools::UserFilesInterface::FileKind::image) {
                attachedFilesField->addFile(filePath);
            }
        }
    }

    setShownDropField(false);

    // restoring saved state
    setSizeHintSize();
}

// if state == true, it shows dropField and hides everything else
// otherwise it makes on the contrary
void G_FastPost::setShownDropField(bool shown) {
    textEdit->setShown(!shown);
    attachedFilesField->setShown(!shown && !attachedFilesField->isEmpty());
    sendButton->setShown(!shown);

    dropField->setShown(shown); // in center - to prevent blinking in Windows

    clearButton->setShown(!shown);
    statusLabel->setShown(!shown);
    useVkSN->setShown(!shown);
}

void G_FastPost::on_useTwiSN_clicked() {
    toggleButtons();
}
