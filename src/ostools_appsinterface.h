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

/**
 * @file ostools_appsinterface.h
 *
 * Header file of OSTools::AppsInterface class.
 */

#ifndef OSTOOLS_OSTOOLS_APPSINTERFACE_H
#define OSTOOLS_OSTOOLS_APPSINTERFACE_H

#include <QObject>
#include <QHash>
#include <QTimer>
#include <QIcon>
#include <QDebug>
#include "ostools_executablefilesinterface.h"

/**
 * @namespace OSTools
 * @brief Contains platform-dependent tools.
 *
 * The code have to be reviewed when porting to another platform.
 */
namespace OSTools {

/**
 * @class OSTools::AppsInterface
 * @brief Is the interface for apps installed on an user's system
 */
class AppsInterface : public QObject
{
    Q_OBJECT

#ifdef Q_OS_LINUX
    struct LocaleInfo {
        inline bool localeInfoExists() const { return (!lang.isEmpty()); }
        QString lang;
        QString encoding;
        bool containsCountryCode;
    };   
#endif

public:
    struct AdditionalAppInfo;
    struct AppInfo;

    explicit AppsInterface(QObject *parent = 0);        ///< The constructor.

    /**
     * @brief Checks whether there is an app with given name #appName.
     * @param appName App name to be checked.
     * @return True, if there is an app with the name #appName, otherwise false.
     */
    inline bool isApp(const QString &appName) const {
        return m_apps.contains(appName);
    }

    /**
     * @brief Launches application with given name #appName.
     * @param appName App name to be launched.
     * @return True, if the app was launched OK, otherwise false.
     */
    inline bool run(const QString &appName) const{
        if (!m_apps.contains(appName))
            return false;
#ifdef Q_OS_WIN
        QString runCommand = '"' + m_apps.value(appName).exec + '"';
#else
        QString runCommand = m_apps.value(appName).exec;
#endif
        return m_exeFiles.run(runCommand);
    }

    AppInfo getAppInfo(const QString &appName) const;   ///< Returns information about app named #appName.

    QList<AppInfo> appsList(const QString &filter = QString()) const;   ///< Returns list of all installed apps filtered by #filter.
    
    /**
     * @struct OSTools::AppsInterface::AdditionalAppInfo
     * @brief Contains all application information necessary for Joly except name.
     */
    struct AdditionalAppInfo {
        QIcon icon;             ///< App icon.
        QString iconPath;       ///< Path to app icon.
        QString exec;           ///< Path to executable file of the application.
        QString runFolder;      ///< Folder we run app in.
#ifdef Q_OS_LINUX
        QString genericName;    ///< Generic name of the application (following FreeDesktop.org standards). Available only in Linux.
        QString keywords;       ///< Keywords for the application (following FreeDesktop.org standards). Available only in Linux.
#endif
    };

    /**
     * @struct OSTools::AppsInterface::AppInfo
     * @brief Contains all application information necessary for Joly.
     */
    struct AppInfo {
        /**
         * @brief Compares this AppInfo structure with another one by the name. Used for sorting.
         * @param other Other OSTools::AppsInterface::AppInfo structure.
         * @return True, if #name is smaller than other.name, otherwise false.
         */
        inline bool operator<(const AppInfo &other) const { return (name < other.name); }
        QString name;                   ///< Name of the application.
        AdditionalAppInfo info;         ///< All application information except name.
        /**
         * @brief Checks whether this AppInfo object is initialised.
         * @return True, if this AppInfo object isn't initialised, otherwise false.
         */
        inline bool isNull() const { return (name.isNull()); }
    };

protected:
    AppInfo extractAppInfoFromFile(const QString &filePath) const;  ///< Returns information extracted from given file #filePath.
    void recursiveEntryList(const QString &dir);    ///< Collects all information about apps in folder #dir.

#ifdef Q_OS_LINUX
    LocaleInfo getLocaleInfo (QString varName) const;   ///< Returns locale information for given variable #varName.
    void setVarDependingOnLocale(QString *var, const QString &varName, const QString &varValue) const;  ///< Sets variable value depending on system locale.
#endif

#ifdef Q_OS_WIN
    QIcon extractAppIcon(const QString &fileName) const;    ///< Extracts application icon from given '*.exe' file #fileName.
#endif

    QList<AppInfo> convertHashToList(const QHash<QString, AdditionalAppInfo> &hash) const;  ///< Converts hash that contains app info objects into the list with the same objects.
    AppInfo convertHashIterToAppInfo(const QHash<QString, AdditionalAppInfo>::ConstIterator &iter) const;   ///< Converts hash iterator that contains app info into the OSTools::AppsInterface::AppInfo object.

protected slots:
    void updateAppsList();   ///< Updates list of apps installed on an user's system.

private:
    static QHash<QString, AdditionalAppInfo> m_apps;    ///< The list of all installed apps by name
    QStringList m_fullEntryList;                        ///< List of all files that links to apps (.lnk files in Windows or .desktop files in Linux) in special folder
    static QTimer m_updateTimer;                        ///< Timer to update the list of entries (OSTools::AppsInterface#m_fullEntryList), see OSTools::AppsInterface::updateAppsList()
    ExecutablesInterface m_exeFiles;                ///< The interface to executable files, see ostools_executablefilesinterface.h
};

} // namespace OSTools

#endif // OSTOOLS_OSTOOLS_APPSINTERFACE_H
