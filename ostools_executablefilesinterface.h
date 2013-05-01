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

#ifndef OSTOOLS_EXECUTABLEFILESINTERFACE_H
#define OSTOOLS_EXECUTABLEFILESINTERFACE_H

#include <QObject>
#include <QUrl>
#include <QSet>
#include <QTimer>
#include <QStringList>

namespace OSTools {

class ExecutablesInterface: public QObject
{
    Q_OBJECT

public:
    ExecutablesInterface(QObject *parent = 0);

    bool isExecutable(const QString &fileName) const;
    inline bool isExecutable(const QUrl &fileName) const {
        return isExecutable(fileName.toString());
    }

    bool run(const QString &fileName) const;
    inline bool run(const QUrl &fileName) const {
        return run(fileName.toString());
    }

    QStringList executablesList(const QString &filter = QString());

protected slots:
    void updateLists();
    void updatePathDirsList();
    void updatePathFilesList();

private:
    static QStringList m_pathDirs;
    static QSet<QString> m_pathFiles;
    static QTimer m_updateTimer;
};

} // namespace OSTools

#endif // OSTOOLS_EXECUTABILITYCHECKER_H
