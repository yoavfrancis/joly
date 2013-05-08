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

#include "apigooglesearch.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QUrlQuery>

ApiGoogleSearch::ApiGoogleSearch(QObject *parent) :
    QObject(parent)
{
}


void ApiGoogleSearch::getSuggestions(const QString &request)
{
    m_currentSuggestionsRequest = request;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(getSuggestionsFinished(QNetworkReply*)));

    QUrl url(m_suggestionsParameters.url);
    QUrlQuery query;
    query.addQueryItem("client", m_suggestionsParameters.client);
    query.addQueryItem("q", QUrl::toPercentEncoding(request, "", "+"));
    url.setQuery(query);

    manager->get(QNetworkRequest(url));
}

void ApiGoogleSearch::getSuggestionsFinished(QNetworkReply *reply)
{
    QByteArray content = reply->readAll();

    if (m_suggestionsParameters.client == "chrome") {
        QJsonParseError parseError;

        QVariant json = QJsonDocument::fromJson(content, &parseError).toVariant();
        if (Q_UNLIKELY(parseError.error)) {
            qWarning() << "ApiGoogleSearch::getSuggestionsFinished():"
                       << tr("Can't parse JSON data:") << content
                       << tr(". Parser returned an error:") << parseError.errorString();
            qWarning() << "Request:" << m_currentSuggestionsRequest;
            m_currentSuggestionsRequest.clear();
            emit suggestionsError();
            return;
        }
        QVariantList list = json.toList();

        QVariantList suggestions = list.at(1).toList();
        QVariantList titles = list.at(2).toList();
        QVariantList kinds = list.at(4).toMap().value("google:suggesttype").toList();

        if (Q_UNLIKELY(suggestions.length() != titles.length() || titles.length() != kinds.length())) {
            qWarning() << "ApiGoogleSearch::getSuggestionsFinished():" << "something strange in returned JSON data."
                       << "Maybe data format has been changed?";
            qWarning() << "Request:" << m_currentSuggestionsRequest << "\nRetuned JSON:" << content;
            Q_ASSERT(suggestions.length() == titles.length() && titles.length() == kinds.length());
            emit suggestionsError();
            m_currentSuggestionsRequest.clear();
            return;
        }

        QList<Consts::Shared::Suggestion> suggestionsToReturn;
        for (int i = 0; i < suggestions.length(); ++i) {
            Consts::Shared::Suggestion suggestion;

            // Text
            suggestion.text = suggestions.at(i).toString();

            // Kind
            if (kinds.at(i) == "NAVIGATION")
                suggestion.kind = Consts::Shared::Suggestion::Kind::Navigation;
            else if (kinds.at(i) == "QUERY")
                suggestion.kind = Consts::Shared::Suggestion::Kind::Query;
            else
                continue; // We don't save suggestions with other kinds

            // Others
            if (suggestion.kind == Consts::Shared::Suggestion::Kind::Navigation)
                suggestion.others.linkTitle = titles.at(i).toString();

            suggestionsToReturn.append(suggestion);
        }

        emit suggestionsReceived(m_currentSuggestionsRequest, suggestionsToReturn);
    }

    else {
        emit suggestionsError();
    }

    m_currentSuggestionsRequest.clear();
}
