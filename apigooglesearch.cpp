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

#ifdef Q_OS_WIN
#include <QJson/include/QJson/Parser>
#elif defined (Q_OS_LINUX)
#include <qjson/parser.h>
#endif

ApiGoogleSearch::ApiGoogleSearch(QObject *parent) :
    QObject(parent)
{
}


void ApiGoogleSearch::getSuggestions(const QString &request)
{
    m_lastSuggestionsRequest = request;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(getSuggestionsFinished(QNetworkReply*)));

    QUrl url("http://suggestqueries.google.com/complete/search");
    url.addQueryItem("client", "chrome");
    url.addEncodedQueryItem("q", QUrl::toPercentEncoding(request, "", "+"));
    qDebug() << "ApiGoogleSearch::getSuggestions():" << url;

    manager->get(QNetworkRequest(url));
    qDebug() << "After-get debug";
}

void ApiGoogleSearch::getSuggestionsFinished(QNetworkReply *reply)
{
    qDebug() << "ApiGoogleSearch::getSuggestionsFinished() started";
    QByteArray replyContent = reply->readAll();

    QJson::Parser parser;
    bool ok;

    QVariantList result = parser.parse(replyContent, &ok).toList();
    if (Q_UNLIKELY(!ok)) {
        qWarning() << "ApiGoogleSearch::getSuggestionsFinished():" << "error parsing JSON data:"
                   << parser.errorString() << "at" << parser.errorLine();
        qWarning() << "Request:" << m_lastSuggestionsRequest << "\nReturned JSON:" << replyContent;
        m_lastSuggestionsRequest.clear();
        return;
    }

    QVariantList suggestions = result.at(1).toList();
    QVariantList titles = result.at(2).toList();
    QVariantList kinds = result.at(4).toMap().value("google:suggesttype").toList();

    if (Q_UNLIKELY(suggestions.length() != titles.length() || titles.length() != kinds.length())) {
        qWarning() << "ApiGoogleSearch::getSuggestionsFinished():" << "something strange in returned JSON data."
                   << "Maybe data format has been changed?";
        qWarning() << "Request:" << m_lastSuggestionsRequest << "\nRetuned JSON:" << replyContent;
        Q_ASSERT(suggestions.length() == titles.length() && titles.length() == kinds.length());
        m_lastSuggestionsRequest.clear();
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

    emit suggestionsReceived(m_lastSuggestionsRequest, suggestionsToReturn);

    m_lastSuggestionsRequest.clear();
}
