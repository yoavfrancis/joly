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

#include "ostools_appsinterface.h"

#include <QDir>
#include <QTextStream>
#include <QProcessEnvironment>
#include <QDebug>
#include <QSettings>
#include <QTimer>
#include <QFileIconProvider>
#include "consts.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#endif


#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

QHash <QString, OSTools::AppsInterface::AdditionalAppInfo> OSTools::AppsInterface::m_apps;
QTimer OSTools::AppsInterface::m_updateTimer;

/**
 * @brief Constructs an OSTools::AppsInterface::AppsInterface object.
 * @param parent The parent of an OSTools::AppsInterface::AppsInterface object.
 */
OSTools::AppsInterface::AppsInterface(QObject *parent) :
    QObject(parent)
{
    // lauching updateAppList() in separate thread to prevent freezing of program at the start
    // if m_apps is already filled in other copy of AppsInterface object, we do nothing
    if (m_apps.isEmpty()) {
        QTimer *initTimer = new QTimer;
        initTimer->setSingleShot(true);
        connect(initTimer, SIGNAL(timeout()), SLOT(updateAppsList()));
        connect(initTimer, SIGNAL(timeout()), initTimer, SLOT(deleteLater()));
        initTimer->start(1);
    }

    // configuring regural updating of app list
    // if m_updateTimer is already running (started in other copy of AppsInterface object), we do nothing
    if (!m_updateTimer.isActive()) {
        const qint32 millisecondsIn10Minutes = 600000;
        connect(&m_updateTimer, SIGNAL(timeout()), SLOT(updateAppsList()));
        m_updateTimer.start(millisecondsIn10Minutes);
    }
}


/**
 * @brief Updates list of apps installed on an user's system.
 *
 * The method contains different code for different OSs.
 * On the Linux, it uses specifications of the http://freedesktop.org.
 * On the Windows, it scans the Start menu folder.
 */
void OSTools::AppsInterface::updateAppsList() {
    m_fullEntryList.clear();
    m_apps.clear();

#ifdef Q_OS_LINUX
    /*
     * Getting list of dirs where could be "applications" dir located.
     * Look http://standards.freedesktop.org/menu-spec/latest/ar01s02.html.
     */
    QProcessEnvironment systemEnvironment = QProcessEnvironment::systemEnvironment();
    QStringList dataDirs = systemEnvironment.value("XDG_DATA_DIRS").split(':');
    if (dataDirs.isEmpty()) {
        dataDirs << "/usr/local/share/" << "/usr/share/";
        // Look http://standards.freedesktop.org/basedir-spec/latest/ar01s03.html.
    }

    // Getting the list of the dirs where ".desktop" files for apps could be located.
    QStringList appsDirs;
    forc11 (QString dir, dataDirs) {
        if (!dir.endsWith('/'))
            dir.append('/');
        appsDirs.append(dir + "applications/");
    }

    // Getting the list of the ".desktop" files in the dirs and subdirs in #appsDirs list.
    m_fullEntryList.clear();

    forc11 (const QString &str, appsDirs) {
        recursiveEntryList(str);
    }

    /*
     * processing all items in m_fullEntryList and saving the app name, the generic app name,
     * the path to app icon, and the path to app to m_apps.
     * Note: you can read freedesktop specification for .desktop files here:
     * http://standards.freedesktop.org/desktop-entry-spec/latest/.
     */
    forc11 (const QString &desktopEntry, m_fullEntryList) {
        AppInfo app = extractAppInfoFromFile(desktopEntry);
        if (!app.isNull())
            m_apps.insertMulti(app.name, app.info);
    }

#elif defined (Q_OS_WIN)
    // We use the Start menu folder as the folder where all necessary apps are listed.
    QSettings settings1("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders",
                        QSettings::NativeFormat);
    QSettings settings2("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders",
                        QSettings::NativeFormat);

    QString winStyleSeparator = QDir::separator();
    QString qtStyleSeparator = "/";

    QStringList appsDirs;
    appsDirs << settings1.value("Common Start Menu").toString().replace(winStyleSeparator, qtStyleSeparator)
             << settings2.value("Start Menu").toString().replace(winStyleSeparator, qtStyleSeparator);


    // Getting the list of the ".lnk" files in the dirs and subdirs in #startMenuPaths.
    m_fullEntryList.clear();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString programData = env.value("ProgramData");
    if (programData.endsWith(QDir::separator()))
        programData.chop(1);
    QString userProfile = env.value("USERPROFILE");
    if (userProfile.endsWith(QDir::separator()))
        userProfile.chop(1);
    forc11 (QString path, appsDirs) {
        path.replace("%ProgramData%", programData, Qt::CaseInsensitive)
            .replace("%USERPROFILE%", userProfile, Qt::CaseInsensitive);
        recursiveEntryList(path);
    }

    // Processing all items in m_fullEntryList and saving the app name, the path to app icon, and the path to app to m_apps
    forc11 (const QString &desktopEntry, m_fullEntryList) {
        AppInfo app = extractAppInfoFromFile(desktopEntry);
        if (!app.isNull())
            m_apps.insertMulti(app.name, app.info);
    }


#else
#error This OS is not supported in OSTools::AppsInterface class
#endif

}

// this method processes given app file
/**
 * @brief Analyses given app file and returns all information extracted from it.
 * @param filePath Path to app file.
 * @return Information extracted from given #filePath file.
 *
 * 'App file' means *.desktop file for Linux and *.lnk file for Windows.
 * The method contains different code for different OSs.
 * On the Linux, it uses specifications of the http://freedesktop.org.
 */
OSTools::AppsInterface::AppInfo OSTools::AppsInterface::extractAppInfoFromFile(const QString &filePath) const {

#ifdef Q_OS_LINUX

    QFile file(filePath);
    if (Q_UNLIKELY(!file.open(QIODevice::ReadOnly))) {
        qWarning() << "something is strange: file" << filePath << "can't be opened";
        Q_ASSERT_X(false, "updating app list", qPrintable(QString("something is strange: file ") + filePath + " can't be opened"));
        return AppInfo();
    }

    QTextStream in(&file);
    bool desktopEntryGroup = false;

    AppInfo app;
    bool saveThisApp = true;

    // getting current desktop enviroment name
    // look http://enzotib.blogspot.com/2012/04/environment-variables-to-distinguish.html
    const QString currentDesktop = QProcessEnvironment::systemEnvironment().value("XDG_CURRENT_DESKTOP");

    // processing file; see http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s02.html
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // replacing possible escape sequences; look http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s03.html
        line.replace("\\s", " ");
        line.replace("\\n", "\n");
        line.replace("\\t", "\t");
        line.replace("\\r", "\r");
        line.replace("\\\\", "\\");

        // if it's a comment or an empty line
        if (line.isEmpty() || line.startsWith('#'))
            continue;

        // if it's the title of the "Desktop Entry" group
        // it's the group that contains the needed variables
        if (line == "[Desktop Entry]") {
            desktopEntryGroup = true;
            continue;
        }

        // if it's the title of the other group
        if (line.startsWith('[')) {
            // we are leaving the loop if desktopEntryGroup == true, i.e. if this group was already processed
            // there won't be continuations of it in this file
            if (desktopEntryGroup)
                break;
            else
                continue;
        }

        // now it's (most likely) variable
        QStringList separatedLine = line.split('=');

        // prevending wrong format of file
        if (Q_UNLIKELY(separatedLine.length() != 2)) {
            qWarning() << qPrintable(tr("Could not process file %1 in AppsInterface: wrong format of line %2").arg(filePath).arg(line));
            saveThisApp = false;
            break;
        }

        QString varName = separatedLine.first().trimmed();
        QString varValue = separatedLine.last().trimmed();

        // processing variable; look http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s05.html
        if (varName == "Type") {

            if (varValue != "Application") {
                // we must process only applications
                // nothing to do in this file
                saveThisApp = false;
                break;
            }

        }
        else if (varName.startsWith("Name")) {

            setVarDependingOnLocale(&app.name, varName, varValue);

        }
        else if (varName.startsWith("GenericName")) {

            setVarDependingOnLocale(&app.info.genericName, varName, varValue);

        }
        else if (varName == "NoDisplay" || varName == "Hidden") {

            // by specification, we must don't display entries that have parameter "NoDisplay" or "Hidden" equaling true
            if (varValue == "true") {
                saveThisApp = false;
                break;
            }
            // but if it equals false, we will display it
            else {
                continue;
            }

        }
        else if (varName.startsWith("Icon")) {

            // we don't search for this icon by specifications at http://freedesktop.org/wiki/Specifications/icon-theme-spec?action=show&redirect=Standards%2Ficon-theme-spec
            // we can simply call QIcon::fromTheme later.
            QString appIcon;

            setVarDependingOnLocale(&appIcon, varName, varValue);

            app.info.iconPath = appIcon;

            // if it's path to icon
            if (appIcon.contains( QDir::separator() )) {
                app.info.icon = QIcon(appIcon);
            } else {
                app.info.icon = QIcon::fromTheme(appIcon, QIcon::fromTheme("application-x-executable"));
            }

        }
        else if (varName == "OnlyShowIn") {
            QStringList onlyShowIn = varValue.split(';', QString::SkipEmptyParts);

            // if current environment isn't in list of enviroments where we must display this item
            if (!onlyShowIn.contains(currentDesktop)) {
                saveThisApp = false;
                break;
            }

        }
        else if (varName == "NotShowIn") {
            QStringList notShowIn = varValue.split(';', QString::SkipEmptyParts);

            // if current environment isn't in list of enviroments where we must display this item
            if (notShowIn.contains(currentDesktop)) {
                saveThisApp = false;
                break;
            }

        }
        else if (varName == "TryExec") {

            if (!m_exeFiles.isExecutable(varValue)) {
                // we must ignore this item
                saveThisApp = false;
                break;
            }

        }
        else if (varName == "Exec") {

            app.info.exec = varValue;

        }
        else if (varName == "Path") {

            app.info.runFolder = varValue;

        }
        else if (varName == "Keywords") {

            app.info.keywords = varValue;

        }

    } // one-file loop (while (!in.atEnd()))

    if (saveThisApp) {

        // making some additional work

        // replacing parameters like "%s"; look http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s06.html
        QString &appExec = app.info.exec;

        // we're removing them because we don't open any files with this app
        appExec.remove("%f");
        appExec.remove("%F");
        appExec.remove("%u");
        appExec.remove("%U");

        // we're removing them because they're deprecated
        appExec.remove("%d");
        appExec.remove("%D");
        appExec.remove("%n");
        appExec.remove("%N");
        appExec.remove("%v");
        appExec.remove("%m");

        // replacing by specification
        appExec.replace("%i", QString("--icon %1").arg(app.info.iconPath));
        appExec.replace("%c", app.name);
        appExec.replace("%k", filePath);

        return app;
    }

    return AppInfo();

#elif defined(Q_OS_WIN)

    QFileInfo file(filePath);
    // if targer doesn't exist
    if (!QFileInfo( file.symLinkTarget() ).exists())
        return AppInfo();

    QString fileSuffix = QFileInfo( file.symLinkTarget() ).suffix();
    if (fileSuffix != "exe" && fileSuffix != "com" && fileSuffix != "bat" && fileSuffix != "cmd")
        return AppInfo();

    AppInfo app;

    app.name = file.completeBaseName();
    app.info.exec = file.symLinkTarget();
    app.info.icon = extractAppIcon(file.symLinkTarget());

    return app;

#else
#error This OS is not supported in OSTools::AppsInterface class
#endif

}


/**
 * @brief Saves all app files' paths from the given #dir folder and all its subdirs.
 * @param dir Folder to save files' paths from.
 *
 * It recurcively goes through all subfolders in given #dir folder
 * and saves paths of found app files to OSTools::AppsInterface#m_fullEntryList.
 */
void OSTools::AppsInterface::recursiveEntryList(const QString &dir) {
    QDir currDir(dir);

    QString appFileExtension;
#ifdef Q_OS_LINUX
    appFileExtension = "desktop";
#elif defined(Q_OS_WIN)
    appFileExtension = "lnk";
#else
#error Unknown app file extension
#endif

    QFileInfoList entries = currDir.entryInfoList(QDir::AllEntries | QDir::NoDot | QDir::NoDotDot);

    forc11 (const QFileInfo &entry, entries) {
        QString entryFilePath = entry.absoluteFilePath();
        // the next "if" prevents "looping" when a file links to the folder we are currently in
        if ( !(entry.isSymLink() && entry.symLinkTarget() == entryFilePath) ) {
            if (entry.isDir()) {
                recursiveEntryList(entryFilePath);
            } else {
                if (entry.suffix() == appFileExtension)
                    m_fullEntryList.append(entryFilePath);
            }
        }
    }
}

#ifdef Q_OS_LINUX
/**
 * @brief Returns locale information (language code, encoding etc) for given variable #varName.
 * @param varName The variable name to return locale information for.
 * @return Locale information for given variable #varName.
 *
 * Look http://standards.freedesktop.org/desktop-entry-spec/latest/ar01s04.html.
 */
OSTools::AppsInterface::LocaleInfo OSTools::AppsInterface::getLocaleInfo(QString varName) const {
    LocaleInfo localeInfo;

    if (varName.contains('[')) {
        // isolating locale
        QString locale = varName;
        locale.remove(QRegExp("*[", Qt::CaseInsensitive, QRegExp::Wildcard));
        locale.remove(']');

        // removing @MODIFIER
        locale.remove(QRegExp("@*", Qt::CaseInsensitive, QRegExp::Wildcard));

        // splitting locale to components
        if (locale.contains('.')) {
            QStringList localeComponents = locale.split('.');
            localeInfo.lang = localeComponents.first();
            localeInfo.encoding = localeComponents.last();
        } else {
            localeInfo.lang = locale;
        }

        localeInfo.containsCountryCode = localeInfo.lang.contains('_'); // '_' is separator between the language code and the country code
    }

    return localeInfo;
}

/**
 * @brief Sets variable value depending on system locale.
 *
 * I can't actually remember what does it do. :(
 */
void OSTools::AppsInterface::setVarDependingOnLocale(QString *var, const QString &varName, const QString &varValue) const {
    LocaleInfo locale = getLocaleInfo(varName);

    // if there is the locale info in this varName
    if (locale.localeInfoExists()) {

        // getting current language name
        // QLocale::name returns smth like "en_US"
        QString currLang = QLocale().name();

        // if locale.lang == "en_US"
        if (locale.lang == currLang || locale.lang == currLang.split('_').first()) {
            *var = varValue;
        }
    } else {
        // if we still didn't set localized version of name
        if (var->isNull())
            *var = varValue;
    }
}
#endif

#ifdef Q_OS_WIN
/**
 * @brief Extracts application icon from given file #fileName.
 * @param fileName file to extract app icon from.
 * @return QIcon object that represents extracted icon.
 */
QIcon OSTools::AppsInterface::extractAppIcon(const QString &fileName) const {
    /*wchar_t *convertedName = new wchar_t[fileName.length() + 1];
    fileName.toWCharArray(convertedName);

    convertedName[fileName.length()] = '\0';

    HINSTANCE hInst = GetModuleHandle(NULL);
    HICON Icon = ExtractIcon(hInst, convertedName, 0);

    QPixmap pixmap;

    if (GetLastError() != 0) {
        Icon = LoadIcon(NULL, IDI_APPLICATION);
        pixmap = QPixmap::fromWinHICON(Icon);
    } else {
        pixmap = QPixmap::fromWinHICON(Icon);
    }*/

    return QFileIconProvider().icon(QFileInfo(fileName));

//    return QIcon(pixmap);
}
#endif

/**
 * @brief Returns information about app named #appName.
 * @param appName The application name to return information about.
 * @return AppInfo object that contains information about app.
 */
OSTools::AppsInterface::AppInfo OSTools::AppsInterface::getAppInfo(const QString &appName) const {
    AppInfo appInfo;

    // if app list contains app with name "appName"
    if (m_apps.contains(appName)) {
        appInfo.info = m_apps.value(appName);
        // we made it in 'if' because we want user can check app existence by calling appInfo.appInfoExists()
        appInfo.name = appName;
    }

    return appInfo;
}

/**
 * @brief Returns list of all installed apps filtered by #filter.
 * @param filter The filter text for the apps.
 * @return List of the AppInfo objects.
 *
 * If #filter is empty, it returns the whole list of apps.
 * Otherwise the following condition is applied:
 * appName.startsWith(filter) or genericAppName.contains(filter) or appKeywords.contains(filter).
 */
QList<OSTools::AppsInterface::AppInfo> OSTools::AppsInterface::appsList(const QString &filter) const {
    // all map is matching empty filter
    if (filter.isEmpty())
        return convertHashToList(m_apps);

    QList<AppInfo> byNameList;
#ifdef Q_OS_LINUX
    QList<AppInfo> byKeywordsList;
    QList<AppInfo> byGenericNameList;
#endif
    for (auto iter = m_apps.constBegin(); iter != m_apps.constEnd(); ++iter) {
        // if name starts with "filter"
        if ( iter.key().contains(filter, Qt::CaseInsensitive) ) {
            byNameList.append(convertHashIterToAppInfo(iter));
        }
#ifdef Q_OS_LINUX
        // if keywords string contains "filter"
        else if  (iter->keywords.contains(filter, Qt::CaseInsensitive) ) {
            byKeywordsList.append(convertHashIterToAppInfo(iter));
        }
        // if generic name contains "filter"
        else if ( iter->genericName.contains(filter, Qt::CaseInsensitive) ) {
            byGenericNameList.append(convertHashIterToAppInfo(iter));
        }
#endif
    }

    QList<AppInfo> result;
    result += byNameList;
#ifdef Q_OS_LINUX
    result += byKeywordsList + byGenericNameList;
#endif

    return result;
}

/**
 * @brief Converts hash that contains app info objects into the list with the same objects.
 * @param hash The hash to convert.
 * @return Converted list.
 */
QList<OSTools::AppsInterface::AppInfo> OSTools::AppsInterface::convertHashToList(const QHash<QString, OSTools::AppsInterface::AdditionalAppInfo> &hash) const {
    QList<AppInfo> converted;

    for (QHash<QString, AdditionalAppInfo>::ConstIterator iter = hash.constBegin(); iter != hash.constEnd(); ++iter) {
        AppInfo app;
        app.name = iter.key();
        app.info = iter.value();

        converted.append(app);
    }

    return converted;
}

// converts QHash<QString, OSTools::AppsInterface::AdditionalAppInfo>::ConstIterator to OSTools::AppsInterface::AppInfo
// it simply sets key of iterator to AppInfo::name, and value to AppInfo::info
/**
 * @brief Converts hash iterator that contains app info into the OSTools::AppsInterface::AppInfo object.
 * @param iter The iterator to convert.
 * @return AppInfo object.
 */
OSTools::AppsInterface::AppInfo OSTools::AppsInterface::convertHashIterToAppInfo(const QHash<QString, OSTools::AppsInterface::AdditionalAppInfo>::ConstIterator &iter) const {
    AppInfo app;
    app.name = iter.key();
    app.info = iter.value();
    return app;
}
