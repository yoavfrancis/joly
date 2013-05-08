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
#include "consts.h"
#include "g_globalline.h"
#include "g_abstractgadget.h"
#include "_lineedit.h"
#include "ostools.h"
#include "strtools.h"
#include "g_globalline_completeritem.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDir>
#include <QtScript/QScriptValue>

#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

/* Functions for script engline */

QScriptValue mySqrt(QScriptContext *context, QScriptEngine *engine) {
    Q_UNUSED(engine)
    QScriptValue value = context->argument(0);
    return qSqrt(value.toNumber());
}

/* Other functions */
// AWUT == ActionsWithUseTimes
// T should be iterator
template<typename Iterator>
inline G_GlobalLine::ActionKind getActionKindFromAWUT(const Iterator& iter) {
    return G_GlobalLine::ActionKind((*iter).split(G_GlobalLine::secondarySeparator).first().toInt());
}

// AWUT == ActionsWithUseTimes
// T should be iterator
template<typename Iterator>
inline int getActionUseTimesFromAWUT(const Iterator& iter) {
    return (*iter).split(G_GlobalLine::secondarySeparator).last().toInt();
}

// T should be iterator
template<typename Iterator>
inline G_GlobalLine::ActionKind getActionKindFromString(const QString& str) {
    return str.split(G_GlobalLine::secondarySeparator).first().toInt();
}

// AWUT == ActionsWithUseTimes
// T should be iterator
template<typename Iterator>
inline int getActionUseTimesFromString(const QString& str) {
    return str.split(G_GlobalLine::secondarySeparator).last().toInt();
}

/* Methods */
G_GlobalLine::G_GlobalLine(QWidget* parent) :
    G_AbstractGadget(parent), m_domains(nullptr), m_skipRunningStr(false)
{
    setupUi(this);
    readSettings();
    setGadgetName("GlobalLine Gadget");

    connect(&m_completer, SIGNAL(activated(CompleterItem::Content)), SLOT(runCompleterItem(CompleterItem::Content)));
    connect(globStr, SIGNAL(returnPressed()), this, SLOT(runStr()));
    connect(globStr, SIGNAL(escapePressed()), &m_completer, SLOT(hide()));
    connect(globStr, SIGNAL(textChanged(QString)), this, SLOT(completeStr(QString)));
    connect(globStr, SIGNAL(keyUpPressed()), &m_completer, SLOT(moveFocusUp()));
    connect(globStr, SIGNAL(keyDownPressed()), SLOT(processKeyDown()));
    connect(&m_apiYandexSearch, SIGNAL(suggestionsReceived(QString,QList<Consts::Shared::Suggestion>)),
            SLOT(suggestionsReceived(QString,QList<Consts::Shared::Suggestion>)));
}

// This function creates competition list for given "str" and shows it by Completer
// TOMODIFY when adding section
void G_GlobalLine::completeStr(const QString &str) {
    QString completingStr = str;
    if (str.trimmed().isEmpty()) {
        m_completer.clear();
        return;
    }

    // Creating ALL actions that we use below
    m_actions.defaultSection =          Actions() << convertStringToAction(completingStr);
    m_actions.launchedSection =         filterLaunchedActions(completingStr);
    m_actions.contentDependentSection = getContentDependentActions(completingStr, m_actions.launchedSection);
    m_actions.appsSection =             getAppsActions(completingStr, m_actions.launchedSection);
    if (completingStr.length() >= 4)
        m_actions.filesSection =        getFilesActions(completingStr, m_actions.launchedSection);
    else
        m_actions.filesSection.clear();
    m_actions.commandsSection =         getCommandsActions(completingStr, m_actions.launchedSection);

    m_apiYandexSearch.getSuggestions(str);

    if (m_actions.filesSection.length() > 25) {
        auto it = m_actions.filesSection.begin();
        it += 25;
        m_actions.filesSection.erase(it, m_actions.filesSection.end());
    }

    // Removing dublicates
    m_actions.launchedSection.removeOne(m_actions.defaultAction());
    m_actions.contentDependentSection.removeOne(m_actions.defaultAction());
    m_actions.appsSection.removeOne(m_actions.defaultAction());
    m_actions.filesSection.removeOne(m_actions.defaultAction());
    m_actions.commandsSection.removeOne(m_actions.defaultAction());


    {
        /* It "solves" the problem:
         * By default "mutter --replace" is search,
         * because there's no file "mutter --replace",
         * but there is file "mutter".
         * That requests are hard to understand, so this is temporary solution
         */
        Action action(completingStr, ActionKind::command);
        if (!m_actions.commandsSection.contains(action))
            m_actions.commandsSection.append(action);
    }

    // Converting ALL actions to CompleterItemContent objects
    // Note: the code is very similar in all for-loops.
    QList<CompleterItemContent> defaultActionsConverted;
    for (uint i = 0; i < uint(m_actions.defaultSection.length()); ++i) {
        auto pos = CompleterItem::Position(CompleterItem::Position::Section::Default, i);
        CompleterItemContent convertedAction = convertActionToCompleterItemContent(m_actions.defaultSection.at(i), pos);
        defaultActionsConverted.append(convertedAction);
    }

    QList<CompleterItemContent> launchedActionsConverted;
    for (uint i = 0; i < uint(m_actions.launchedSection.length()); ++i) {
        auto pos = CompleterItem::Position(CompleterItem::Position::Section::Launched, i);
        CompleterItemContent convertedAction = convertActionToCompleterItemContent(m_actions.launchedSection.at(i), pos);
        launchedActionsConverted.append(convertedAction);
    }

    QList<CompleterItemContent> contentDependentActionsConverted;
    for (uint i = 0; i < uint(m_actions.contentDependentSection.length()); ++i) {
        auto pos = CompleterItem::Position(CompleterItem::Position::Section::ContentDependent, i);
        CompleterItemContent convertedAction = convertActionToCompleterItemContent(m_actions.contentDependentSection.at(i), pos);
        contentDependentActionsConverted.append(convertedAction);
    }

    QList<CompleterItemContent> appsActionsConverted;
    for (uint i = 0; i < uint(m_actions.appsSection.length()); ++i) {
        auto pos = CompleterItem::Position(CompleterItem::Position::Section::Apps, i);
        CompleterItemContent convertedAction = convertActionToCompleterItemContent(m_actions.appsSection.at(i), pos);
        appsActionsConverted.append(convertedAction);
    }

    QList<CompleterItemContent> filesActionsConverted;
    for (uint i = 0; i < uint(m_actions.filesSection.length()); ++i) {
        auto pos = CompleterItem::Position(CompleterItem::Position::Section::Files, i);
        CompleterItemContent convertedAction = convertActionToCompleterItemContent(m_actions.filesSection.at(i), pos);
        filesActionsConverted.append(convertedAction);
    }

    QList<CompleterItemContent> commandsActionsConverted;
    for (uint i = 0; i < uint(m_actions.commandsSection.length()); ++i) {
        auto pos = CompleterItem::Position(CompleterItem::Position::Section::Commands, i);
        CompleterItemContent convertedAction = convertActionToCompleterItemContent(m_actions.commandsSection.at(i), pos);
        commandsActionsConverted.append(convertedAction);
    }

    // Completing
    if (!m_completer.getBasicWidget())
        m_completer.setBasicWidget(globStr);
    m_completer.setDefaultSection(defaultActionsConverted);
    m_completer.setSearchSuggestions(QList<CompleterItemContent>());
    m_completer.setLaunchedSection(launchedActionsConverted);
    m_completer.setContentDependentSection(contentDependentActionsConverted);
    m_completer.setAppsSection(appsActionsConverted);
    m_completer.setFilesSection(filesActionsConverted);
    m_completer.setCommandsSection(commandsActionsConverted);
    m_completer.restoreFocus();
    m_completer.complete();
}

// This function is called when user press Enter in the input field.
// It gets current active completer item id and runs it.
void G_GlobalLine::runStr()
{
    if (globStr->text().isEmpty())
        return;

    if (m_completer.isVisible()) {
        runCompleterItem(m_completer.getFocusedItemContent());
    } else {
        runCompleterItem(m_completer.itemAt(CompleterItem::Position(CompleterItem::Position::Section::Default, 0)));
    }
}

// Runs given completer item
void G_GlobalLine::runCompleterItem(CompleterItem::Content item)
{
    auto itemSection = item.pos.section;
    uint itemId = item.pos.id;
    Q_ASSERT(item.pos.id < uint(m_actions.actionsForSection(itemSection).length()));
    qDebug() << "<rA>";
    runAction(m_actions.actionsForSection(itemSection).at(itemId));
    qDebug() << "</rA>";
}

void G_GlobalLine::suggestionsReceived(const QString &request, const QList<Consts::Shared::Suggestion> &suggestions)
{
    m_actions.searchSuggestionsSection.clear();

    // If suggestions was received too late and text in globstr was already changed
    if (request != globStr->text())
        return;

    // Converting suggestions to actions
    forc11 (const Consts::Shared::Suggestion &suggestion, suggestions) {
        Action action;
        action.text = suggestion.text;

        switch (suggestion.kind) {
        case Consts::Shared::Suggestion::Kind::Navigation:
            action.kind = ActionKind::website;
            action.others.linkTitle = suggestion.others.linkTitle;
            break;
        case Consts::Shared::Suggestion::Kind::Query:
            action.kind = ActionKind::internetSearch;
            break;
        case Consts::Shared::Suggestion::Kind::Fact:
            action.kind = ActionKind::internetSearch;
            action.others.fact = suggestion.others.fact;
            break;
        default:
            Q_ASSERT_X(false, "G_GlobalLine::suggestionsReceived()", "unaccounted parameter of switch");
            action.kind = ActionKind::noKind;
        }

        bool actionCanBeAdded = true;
        // If search suggestions API returns smth like "example.com" and marks it as search query,
        // we display such suggestion as website or email, not like internet search.
        if (suggestion.kind == Consts::Shared::Suggestion::Kind::Query) {
            Action convertedAction = convertStringToAction(suggestion.text);
            if (convertedAction.kind == ActionKind::website || convertedAction.kind == ActionKind::email) {
                action.kind = convertedAction.kind;
            }
        }

        // If convertedAction is already default or is contained in content-dependent section,
        // we don't add it.
        if (action == m_actions.defaultAction())
            actionCanBeAdded = false;

        forc11 (Action act, m_actions.contentDependentSection) {
            if (action == act) {
                actionCanBeAdded = false;
            }
        }

        if (actionCanBeAdded)
            m_actions.searchSuggestionsSection.append(action);
    }

    // Converting actions to CompleterItems
    QList<CompleterItemContent> suggestionsActionsConverted;
    for (uint i = 0; i < uint(m_actions.searchSuggestionsSection.length()); ++i) {
        auto pos = CompleterItem::Position(CompleterItem::Position::Section::SearchSuggestions, i);
        CompleterItemContent convertedAction = convertActionToCompleterItemContent(m_actions.searchSuggestionsSection.at(i), pos);
        suggestionsActionsConverted.append(convertedAction);
    }

    // Limiting search suggestions up to 5 items
    QList<CompleterItemContent> suggestionsActionsConvertedLimited;
    if (suggestionsActionsConverted.length() > 5) {
        suggestionsActionsConvertedLimited << suggestionsActionsConverted.at(0)
                                       << suggestionsActionsConverted.at(1)
                                       << suggestionsActionsConverted.at(2)
                                       << suggestionsActionsConverted.at(3)
                                       << suggestionsActionsConverted.at(4);
    } else {
        suggestionsActionsConvertedLimited = suggestionsActionsConverted;
    }

    m_completer.setSearchSuggestions(suggestionsActionsConvertedLimited);
    m_completer.updateHeight();
}

// Runs given action
void G_GlobalLine::runAction(Action action) {
#ifdef WIN_OLD_COMPILER
#define ActionKind G_GlobalLine
#endif

    switch (action.kind) {
    case ActionKind::app:
        qDebug() << m_apps.getAppInfo(action.text).info.exec;
        m_apps.run(action.text);
        break;

    case ActionKind::abbr:
            // TO DO
        break;

    case ActionKind::twitter:
    {
        QString userName = action.text;
        userName.remove('@');
        OSTools::http("http://twitter.com/" + userName);
        break;
    }

    case ActionKind::website:
        OSTools::http(action.text);
        break;

    case ActionKind::email:
        OSTools::email(action.text);
        break;

    case ActionKind::internetSearch:
    {
        QUrl url("https://google.com/search");
        QUrlQuery query;
        query.addQueryItem("q", QUrl::toPercentEncoding(action.text, "", "+"));
        url.setQuery(query);
        OSTools::http(url);
        break;
    }

    case ActionKind::command:
        m_exes.run(action.text);
        break;

    case ActionKind::file:
        OSTools::file(action.text);
        break;

    case ActionKind::folder:
        OSTools::file(action.text);
        break;

    case ActionKind::calcResult:
            // nothing
        break;

    case ActionKind::noKind:
            // nothing to do here
        break;

    default:
        Q_ASSERT_X(false, "switch", "unaccounted parameter of ActionKind");
    }

#undef ActionKind

    increaceActionUseTimes(action);

    // setting timer to clear globStr.
    // It shouldn't be cleared simply (by calling clear) because of crash
    QTimer *timer = new QTimer;
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), globStr, SLOT(clear()));
    connect(timer, SIGNAL(timeout()), timer, SLOT(deleteLater()));
    timer->start(5);
}

G_GlobalLine::Action G_GlobalLine::convertStringToAction(const QString &str) {
    Action action;
//    if (!StrTools::isAbbr(str)) {     // isAbbr() haven't wrote yet

    if (m_apps.isApp(str)) {
        action = Action(str, ActionKind::app);
    } else {
        if (StrTools::hasSpaces(str)) {
            if (tryAnalyseAsFile(str, &action)) {
                // nothing here. "action" is already completed
            } else {
                action = Action(str, ActionKind::internetSearch);
            }

        } else {
            QUrl url = QUrl(str);
            url.setIdnWhitelist(m_domains->toList());

            if (StrTools::isCorrectHttp(url, m_domains)) {
                action = Action(str, ActionKind::website);
            } else if (StrTools::isCorrectEmail(url, m_domains)) {
                action = Action(str, ActionKind::email);
            } else if (StrTools::isCorrectFtp(url, m_domains)) {
                action = Action(str, ActionKind::website);
            } else if (StrTools::isCorrectTwiUser(str)) {
                action = Action(str, ActionKind::twitter);
            } else {
                if (tryAnalyseAsFile(str, &action)) {
                    // nothing here. "action" is already filled
                } else {
                    action = Action(str, ActionKind::internetSearch);
                }
            }
        }
    }
    return action;
}

CompleterItemContent G_GlobalLine::convertActionToCompleterItemContent(const G_GlobalLine::Action &action,
                                                                       CompleterItem::Position pos)
{
    QPixmap icon;
    if (action.kind == ActionKind::app) {
        icon = action.others.appIcon.pixmap(iconWidth, iconHeigth);
    }
    else {
        icon = iconForActionKind(action.kind).pixmap(iconWidth, iconHeigth);
    }

    QString text;
    if (action.kind == ActionKind::website && !action.others.linkTitle.isEmpty()) {
        text = QString("%1 <font color=grey>(%2)</font>").arg(action.others.linkTitle).arg(action.text);
    }
    else if (action.kind == ActionKind::internetSearch && !action.others.fact.isEmpty()) {
        text = QString::fromUtf8("%1 <font color=grey> — %2</font>").arg(action.text).arg(action.others.fact);
    }
    else if ((action.kind == ActionKind::file || action.kind == ActionKind::folder
              || action.kind == ActionKind::command) && action.text.contains('/')) {
        text = tr("%1 <font color=grey> в %2</font>").arg(QFileInfo(action.text).fileName())
                .arg(QFileInfo(action.text).absoluteFilePath());
    }
    else {
        text = action.text;
    }

    return CompleterItemContent(icon, text, pos);
}

// It tries to analyse given "str" as a file or folder path
// If "str" is the one, function applies changes to "result" and returns true
// Otherwise it returns false
// TODO: modify and move to OSTools::UserFilesInterface
bool G_GlobalLine::tryAnalyseAsFile(const QString &str, G_GlobalLine::Action *result) {
    Action action;
    bool boolResult = false;
    QFileInfo fileInfo (str);
    QString appDir = QDir().path(); // directory where app is working

    if (m_exes.isExecutable(QDir::fromNativeSeparators(str))) {
        // we're calling isExecutable() before exists() because isExecutable() method also
        // checks whether the file name is contained in dirs from PATH variable of shell
        action = Action(str, ActionKind::command);
        boolResult = true;
    } else if (fileInfo.exists() && (fileInfo.isDir() || fileInfo.isFile())) {
        ActionKind kind = fileInfo.isDir() ? ActionKind::file : ActionKind::folder;
        if (fileInfo.path() == appDir) {
            // we don't display files and folders in app's dir
            boolResult = false;
        } else {
            action = Action(str, kind);
            boolResult = true;
        }
    } else {
        boolResult = false;
    }

    if (result) *result = action;
    return boolResult;
}

// Returnes an icon that will be used in the completer for item with action kind "kind"
QIcon G_GlobalLine::iconForActionKind(G_GlobalLine::ActionKind kind) {
#define SET_NECESSARY_ICON_SIZE(ICON) QIcon(QIcon((ICON)).pixmap(iconWidth, iconHeigth))
    switch (kind) {
    case ActionKind::app:
        // nothing to do here
        // icon is already set in completeStr()
        return QIcon();
    case ActionKind::abbr:
        // TO DO
        return QIcon();
    case ActionKind::twitter:
        return /*QIcon(QIcon(":/images/twitter.png").pixmap(iconWidth, iconHeigth))*/SET_NECESSARY_ICON_SIZE(":/images/twitter.png");
    case ActionKind::email:
        return SET_NECESSARY_ICON_SIZE(":/images/email.png");
    case ActionKind::website:
        return SET_NECESSARY_ICON_SIZE(":/images/globe.png");
    case ActionKind::internetSearch:
        return SET_NECESSARY_ICON_SIZE(":/images/search.png");
    case ActionKind::command:
        return SET_NECESSARY_ICON_SIZE(":/images/command.png");
    case ActionKind::folder:
        return SET_NECESSARY_ICON_SIZE(":/images/folder.png");
    case ActionKind::file:
        return SET_NECESSARY_ICON_SIZE(":/images/file.png");
    case ActionKind::calcResult:
        return SET_NECESSARY_ICON_SIZE(":/images/equal.png");
    case ActionKind::noKind:
        // nothing to do here
        return QIcon();
    default:
        Q_ASSERT_X(false, "switch", "unaccounted parameter of ActionKind");
        return QIcon();
    }
#undef SET_NECESSARY_ICON_SIZE
}

// When user runs an action, its use-times count increaces by 1
void G_GlobalLine::increaceActionUseTimes(const G_GlobalLine::Action &action) {
    // If user already launched this action
    if (m_actionsWithUseTimes.contains(action.text)) {
        QStringList values = m_actionsWithUseTimes.values(action.text);

        // Searching right this action in actions with the same text
        bool found = false;
        auto iter = values.begin(); // not constBegin() because we set value to iterator later
        for (; iter != values.end(); ++iter) {
            ActionKind currLoopElemKind = getActionKindFromAWUT(iter)/*->split(secondarySeparator).first().toInt()*/;
            if (currLoopElemKind == action.kind) {
                found = true;
                break;
            }
        }
        // end of searching

        if (found) {
            // increacing use-times count of action by 1
            QStringList splittedValues = iter->split(secondarySeparator);
            splittedValues.last().setNum(splittedValues.last().toULongLong() + 1);
            *iter = splittedValues.join(QChar(char(secondarySeparator)));
        } else {
            // appending the new action with use-times count = 1
            values.append(QString::number(int(action.kind)) + char(secondarySeparator) + '1');
        }

        // saving "values" list to "m_actionsWithPriority"
        m_actionsWithUseTimes.remove(action.text);
        for (QStringList::Iterator iter = values.begin(); iter != values.end(); ++iter) {
            m_actionsWithUseTimes.insertMulti(action.text, *iter);
        }

    } else {
        // appending the new action with use-times count = 1
        m_actionsWithUseTimes.insert(action.text, QString::number(int(action.kind)) + secondarySeparator + '1');
    }
}

void G_GlobalLine::valueChanged(const QString &gadget, const QString &valueName, const QVariant &value) {
    if (gadget != "GlobalLine" && gadget != "all")
        return;

    else if (valueName == "saveEnteredText")
        m_saveEnteredText = value.toBool();
}

void G_GlobalLine::protocolUsed(const QString &gadget, const QString &action, const QVariantMap &parameters) {
    if (gadget != "GlobalLine" && gadget != "all")
        return;

    if (action == "setText") {
        QString text = parameters.value("text").toString();
        globStr->setText(text);
        completeStr(text);
    }
}


void G_GlobalLine::readSettings() {
    QSettings settings;

    settings.beginGroup("GlobalLineGadget");
    move(settings.value("position").toPoint());

    // saveEnteredText
    if (!settings.contains("saveEnteredText"))
        settings.setValue("saveEnteredText", true);
    m_saveEnteredText = settings.value("saveEnteredText").toBool();
    if (m_saveEnteredText)
        globStr->setText(settings.value("text").toString());

    // domains
    m_domains = new QSet<QString>(settings.value("domains").toStringList().toSet());
    if (m_domains->isEmpty())
        OSTools::readListFile(":/resorces/domains.txt", m_domains);

    // actions
    QStringList actions = settings.value("actions").toStringList();
    // every action string is now like: Foo Bar 5|3
    forc11(QString str, actions) {
        QStringList splitted = str.split(mainSeparator);
        m_actionsWithUseTimes.insertMulti(splitted.first(), splitted.last());
    }

    settings.endGroup();
}

void G_GlobalLine::writeSettings() {
    QSettings settings;

    settings.beginGroup("GlobalLineGadget");
    settings.setValue("position", pos());
    settings.setValue("saveEnteredText", m_saveEnteredText);

    if (m_saveEnteredText)
        settings.setValue("text", globStr->text());
    else
        settings.setValue("text", QString());

    settings.setValue("domains", QStringList(m_domains->toList()));


    QStringList actions;
    for(auto iter = m_actionsWithUseTimes.constBegin(); iter != m_actionsWithUseTimes.constEnd(); ++iter) {
        actions += iter.key() + mainSeparator + iter.value();
    }
    settings.setValue("actions", actions);

    settings.endGroup();
}


void G_GlobalLine::closeEvent(QCloseEvent *) {
    writeSettings();
}

// Finding appropriate actions
// Appropriate actions mean actions, which text starts with or ends with "str"
G_GlobalLine::Actions G_GlobalLine::filterLaunchedActions(const QString &textToComplete) {
    // hint: ActionsWithPriority == QHash <QString, QString>
    Actions launchedActions;
    QHash<qint64, ActionsWithUseTimes::ConstIterator> launchesCountList;

    for (auto iter = m_actionsWithUseTimes.constBegin(); iter != m_actionsWithUseTimes.constEnd(); ++iter) {
        QString actionText = iter.key();
        if (actionText.startsWith(textToComplete, Qt::CaseInsensitive) || actionText.endsWith(textToComplete, Qt::CaseInsensitive)) {
            qint64 launchesCount = iter.value().split(secondarySeparator).last().toULongLong();
            launchesCountList.insertMulti(launchesCount, iter);
                // insertMulti(), because more than one action could be called "launchesCount" times
        }
    }


    // sorting appropriate actions under priority in descending order
    // and saving sorted result to launchedActions
    QList <qint64> launchesCounts = launchesCountList.uniqueKeys();
    qSort(launchesCounts.begin(), launchesCounts.end(), qGreater<qint64>());
    for (QList<qint64>::ConstIterator firstLevelIter = launchesCounts.constBegin();
         launchedActions.length() < 5 && firstLevelIter != launchesCounts.constEnd();
         ++firstLevelIter) {

        QList<ActionsWithUseTimes::ConstIterator> valuesList = launchesCountList.values(*firstLevelIter);  // values(), because we call insertMulti() a few lines above

        for (QList<ActionsWithUseTimes::ConstIterator>::ConstIterator secondLevelIter = valuesList.constBegin();
             launchedActions.length() < 5 && secondLevelIter != valuesList.constEnd();
             ++secondLevelIter) {

            Action currAction;

            currAction.text = secondLevelIter->key();
            currAction.kind = ActionKind(secondLevelIter->value().split(secondarySeparator).first().toInt());
                // so,                        "5|3"     -> ("5","3")                     ->  "5" ->  5

            // if current action kind is app, we add app icon from AppsInterface
            if (currAction.kind == ActionKind::app)
                currAction.others.appIcon = m_apps.getAppInfo(currAction.text).info.icon;

            // if current action text not equals text in global line, we add it
            if (currAction.text.toLower() != textToComplete.toLower())
                launchedActions.append(currAction);
        }
    }
    return launchedActions;
}

G_GlobalLine::Actions G_GlobalLine::getContentDependentActions(const QString &textToComplete, const Actions &launchedActions) {
    Actions contentDependentActions;

    if (StrTools::isCorrectDomainName(textToComplete)) {
        Action webAction(textToComplete.toLower() + ".com", ActionKind::website);
        if (!launchedActions.contains(webAction))
            contentDependentActions.append(webAction);

        Action emailAction(textToComplete.toLower() + "@gmail.com", ActionKind::email);
        if (!launchedActions.contains(emailAction))
            contentDependentActions.append(emailAction);
    }

    if (textToComplete.endsWith('.')) {
        // remove the last symbol
        QString truncated = textToComplete;
        truncated.truncate(textToComplete.length()-1);

        if (StrTools::isCorrectDomainName(truncated)) {
            QStringList list;
            list << "com" << "net" << "org";

            forc11 (const QString &str, list) {
                Action action(textToComplete.toLower() + str, ActionKind::website);
                if (!launchedActions.contains(action))
                    contentDependentActions.append(action);
            }
        }
    }
    else if (textToComplete.endsWith('@')) {
        // remove the last symbol
        QString truncated = textToComplete;
        truncated.truncate(textToComplete.length()-1);

        if (StrTools::isCorrectDomainName(truncated)) {
            QStringList list;
            list << "gmail.com" << "hotmail.com";

            forc11 (const QString &str, list) {
                Action action(textToComplete.toLower() + str, ActionKind::email);
                if (!launchedActions.contains(action))
                    contentDependentActions.append(action);
            }
        }
    }

    QScriptValue scrSqrt = m_engine.newFunction(mySqrt);
    m_engine.globalObject().setProperty("sqrt", scrSqrt);
    QScriptValue value = m_engine.evaluate(textToComplete);
    if (value.isNumber()) {
        if (value.toString() != "Infinity" && value.toString() != "NaN")
            contentDependentActions << Action(QString::number(value.toNumber()), ActionKind::calcResult);
    }

    return contentDependentActions;
}

G_GlobalLine::Actions G_GlobalLine::getAppsActions(const QString &textToComplete, const Actions &launchedActions) {
    QList<OSTools::AppsInterface::AppInfo> apps = m_apps.appsList(textToComplete);
    Actions appStartsWithActions;
    Actions appContainsActions;

    for (QList<OSTools::AppsInterface::AppInfo>::size_type i = 0; i < 10 && i < apps.size(); ++i) {
        OSTools::AppsInterface::AppInfo app = apps.value(i);
        Action action(app.name, ActionKind::app);
        if (!launchedActions.contains(action)) {
            action.others.appIcon = QIcon(app.info.icon.pixmap(iconWidth, iconHeigth));
            if (app.name.startsWith(textToComplete))
                appStartsWithActions.append(action);
            else
                appContainsActions.append(action);
        }
    }

    // This is done for the correct order of apps:
    // firstly, apps with name starts with "textToComplete",
    // secondly, apps with name contains (but not starts with) "textToComplete"
    return appStartsWithActions + appContainsActions;
}

G_GlobalLine::Actions G_GlobalLine::getFilesActions(const QString &textToComplete, const G_GlobalLine::Actions &launchedActions)
{
    QStringList files = m_files.filesList(textToComplete);
    files.sort();

    Actions filesActions;
    forc11 (QString str, files) {
        Action action;
        QFileInfo info(str);

        action.text = info.absoluteFilePath();
        if (info.isFile()) {
            if (info.isExecutable())
                action.kind = ActionKind::command;
            else
                action.kind = ActionKind::file;
        }
        else {
            action.kind = ActionKind::folder;
        }

        if (!launchedActions.contains(action))
            filesActions.append(action);
    }
    return filesActions;
}

G_GlobalLine::Actions G_GlobalLine::getCommandsActions(const QString &textToComplete, const Actions &launchedActions) {
    QStringList commands = m_exes.executablesList(textToComplete);
    commands.sort();
    Actions commandsActions;

    for (QStringList::size_type i = 0; i < 10 && i < commands.size(); ++i) {
        Action action(commands.value(i), ActionKind::command);
        if (!launchedActions.contains(action)) {
            commandsActions.append(action);
        }
    }
    return commandsActions;
}
