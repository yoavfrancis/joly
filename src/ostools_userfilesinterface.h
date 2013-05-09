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

#ifndef OSTOOLS_OSTOOLS_FILESINTERFACE_H
#define OSTOOLS_OSTOOLS_FILESINTERFACE_H

#include <QObject>
#include <QMap>

namespace OSTools {

class UserFilesInterface : public QObject
{
    Q_OBJECT

public:
#ifdef WIN_OLD_COMPILER
    enum FileKind {
#else
    enum class FileKind {
#endif
         unknown, image, audio, video, executable, other
    };

    UserFilesInterface(QObject *parent = 0);

    static FileKind getFileKind(const QString &filePath);

    bool isContanedInUserFolder(const QString &fileName);
    QStringList filesList(const QString &filter = QString());

signals:
    void filesAreAvailable();

protected:

protected slots:
    void update();

private:
    static QMap<QString, QString> m_files; // <fileName, filePath>
};

} // namespace OSTools

#endif // OSTOOLS_OSTOOLS_FILESINTERFACE_H
