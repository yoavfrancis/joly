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

#ifndef APIGOOGLESEARCH_H
#define APIGOOGLESEARCH_H

#include <QObject>
#include "consts.h"

class QNetworkReply;

/**
 * @brief The ApiGoogleSearch class is the interface for the Google Search APIs.
 *
 * Currently (2013-05-08) supported functions:
 *   - Search suggestions
 */
class ApiGoogleSearch : public QObject
{
    Q_OBJECT
public:
    explicit ApiGoogleSearch(QObject *parent = 0);

signals:
    void suggestionsReceived(const QString &request, const QList<Consts::Shared::Suggestion> &suggestions);
    void suggestionsError();
    
public slots:
    void getSuggestions(const QString &request);

protected:
    void parseSuggestionsForChrome(const QByteArray &data);

private slots:
    void getSuggestionsFinished(QNetworkReply *reply);

private:
    QString m_currentSuggestionsRequest;

    struct _suggestionsParameters {
        const QString url = "http://suggestqueries.google.com/complete/search";
        const QString client = "chrome";
    } m_suggestionsParameters;
};

#endif // APIGOOGLESEARCH_H
