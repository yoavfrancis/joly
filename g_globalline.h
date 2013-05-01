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

#ifndef G_GLOBALLINE_H
#define G_GLOBALLINE_H

#include "ui_g_globalline.h"
#include "g_abstractgadget.h"
#include "ostools_executablefilesinterface.h"
#include "ostools_appsinterface.h"
#include "ostools_userfilesinterface.h"
#include "g_globalline_completer.h"
#include "apigooglesearch.h"
#include "apiyandexsearch.h"
#include <QPointer>
#include <QMap>
#include <QDir>
#include <QtScript/QScriptEngine>

class GlLineEdit;
class QPushButton;
class QLabel;
class QString;
class QStringList;
class QCompleter;

#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

class G_GlobalLine : public G_AbstractGadget, private Ui::GlobStrGadget
{
    Q_OBJECT

    // enums
#ifdef WIN_OLD_COMPILER
    enum
#else
    enum class
#endif
        ActionKind { noKind, calcResult, file, folder, command, internetSearch, website, email, twitter, abbr, app };
    enum { secondarySeparator = '|', mainSeparator = '\t' };
    // It's used for saving actions in

    // classes
    struct Action {
        Action (QString str = "", ActionKind k = ActionKind::noKind ) { text = str; kind = k; }

        bool operator==(Action act)  { return (text == act.text && kind == act.kind); }
        bool operator==(QString str) { return (text == str); }
        bool operator!=(Action act)  { return (text != act.text || kind != act.kind); }
        bool operator!=(QString str) { return (text != str); }

        QString text;
        ActionKind kind;

        struct _others {
            QIcon appIcon;
            QString linkTitle;
            QString fact;
        } others;
    };

    // type defines
    typedef QList <Action> Actions;
    typedef QHash <QString, QString> ActionsWithUseTimes;
        /*
          Second QString equals QString::number(ActionKind) + '|' + QString::number(qint64),
          Where qint64 is "priority" - count of launches of this request
        */

public:
    explicit G_GlobalLine (QWidget* parent = 0);

signals:

public slots:
    void completeStr (const QString &str);
    void runStr();
    void valueChanged (const QString &gadget, const QString &valueName, const QVariant &value);
    void protocolUsed(const QString &gadget, const QString &action, const QVariantMap &parameters);

protected:
    // events
    void closeEvent (QCloseEvent *event);

    // constructing and destructing
    void readSettings();
    void writeSettings();

    // actions
    void runAction (Action action);
    QIcon iconForActionKind(ActionKind kind);
    Action convertStringToAction(const QString &str);
    CompleterItemContent convertActionToCompleterItemContent(const Action& action, CompleterItem::Position pos);
    void increaceActionUseTimes(const Action &action);
    bool tryAnalyseAsFile(const QString &str, Action *result = 0);
    inline QIcon iconForApp(const QString iconValue) {
        // if "iconValue" is path to icon, but not icon name
        if (iconValue.contains( QDir::separator() ))
            return QIcon(QIcon(iconValue).pixmap(iconWidth, iconHeigth));
        else
            return QIcon( QIcon::fromTheme( iconValue, QIcon(":/images/window.png") ).pixmap(iconWidth, iconHeigth) );
    }
    Actions filterLaunchedActions(const QString &textToComplete);

    // TOMODIFY when adding section (add the function)
    Actions getContentDependentActions(const QString &textToComplete, const Actions &launchedActions);
    Actions getAppsActions(const QString &textToComplete, const Actions &launchedActions);
    Actions getFilesActions(const QString &textToComplete, const Actions &launchedActions);
    Actions getCommandsActions(const QString &textToComplete, const Actions &launchedActions);

protected slots:
    void runCompleterItem (CompleterItem::Content item);
    inline void processKeyDown() {
        if (m_completer.isVisible()) {
            m_completer.moveFocusDown();
        } else {
            m_completer.restoreFocus();
            m_completer.show();
        }
    }
    void suggestionsReceived(const QString &request, const QList<Consts::Shared::Suggestion> &suggestions);

private:
    /* Consts */
    enum { iconWidth = 24, iconHeigth = 24 };

    /* Actions */
    struct _m_actions {
        // TOMODIFY when adding section
        Actions defaultSection;
        Actions searchSuggestionsSection;
        Actions launchedSection;
        Actions contentDependentSection;
        Actions appsSection;
        Actions filesSection;
        Actions commandsSection;

        inline Action defaultAction() { return defaultSection.first(); }

        // TOMODIFY when adding section
        inline Actions &actionsForSection(CompleterItem::Position::Section section) {
            typedef CompleterItem::Position::Section Section;
            switch (section) {
            case Section::Default:
                return defaultSection;
                break;
            case Section::SearchSuggestions:
                return searchSuggestionsSection;
                break;
            case Section::Launched:
                return launchedSection;
                break;
            case Section::ContentDependent:
                return contentDependentSection;
                break;
            case Section::Apps:
                return appsSection;
                break;
            case Section::Files:
                return filesSection;
                break;
            case Section::Commands:
                return commandsSection;
                break;
            default:
                Q_ASSERT_X(false, "_m_actions::actionsForSection", "unaccounted parameter of switch");
                return *(new Actions());
            }
        }
    } m_actions;

    ActionsWithUseTimes m_actionsWithUseTimes;

    /* Interfaces */
    OSTools::AppsInterface m_apps;
    OSTools::ExecutablesInterface m_exes;
    OSTools::UserFilesInterface m_files;

    /* Other vars */
    QSet<QString> *m_domains;   // list of first-level domains
    bool m_saveEnteredText;
    bool m_saveHistory;
    bool m_skipRunningStr;

    /* Apis */
    ApiGoogleSearch m_apiGoogleSearch;
    ApiYandexSearch m_apiYandexSearch;

    /* Ui classes */
    Completer m_completer;

    /* Scripts */
    QScriptEngine m_engine;
};

#endif // G_GLOBALLINE_H
