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

#include "notifierbox.h"
#include <QUrl>
#include "consts.h"

NotifierBox::NotifierBox(QWidget *parent) :
    QWidget(parent)
{
    init();
}

NotifierBox::NotifierBox(const QString &title, const QString &description, QWidget *parent):
    QWidget(parent)
{
    init();

    setTitle(title);
    setDescription(description);
}

void NotifierBox::init() {
    setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setWindowTitle(m_title);
}

void NotifierBox::on_descriptionLabel_linkActivated(const QString &link) {
    QUrl url(link);

    using namespace Consts::Gadgets;
    if (url.scheme() == "jolyapp") {
        QString gadgetName;
        if (url.path() == GlobalLine::name.toLower())
            gadgetName = GlobalLine::name;
        else if (url.path() == Messages::name.toLower())
            gadgetName = Messages::name;
        else if (url.path() == FastPost::name.toLower())
            gadgetName = FastPost::name;
        else
            return;


        QString action = url.queryItemValue("act");

        QVariantMap parameters;
        url.removeQueryItem("act");
        QList<QPair<QString, QString> > list = url.queryItems();
        for (int i = 0; i < list.size(); ++i) {
            parameters[list[i].first] = list[i].second;
        }

        emit linkActivated(gadgetName, action, parameters);
    } else {
        QDesktopServices::openUrl(url);
    }
}
