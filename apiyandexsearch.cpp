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

#include "apiyandexsearch.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QUrlQuery>

ApiYandexSearch::ApiYandexSearch(QObject *parent) :
    QObject(parent)
{
}


void ApiYandexSearch::getSuggestions(const QString &request)
{
    m_lastSuggestionsRequest = request;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(getSuggestionsFinished(QNetworkReply*)));

    QUrl url("http://suggest.yandex.ua/suggest-ya.cgi");
    QUrlQuery query;
    query.addQueryItem("v", "4");
    query.addQueryItem("fact", "1");
    query.addQueryItem("part", QUrl::toPercentEncoding(request, "", "+"));
    url.setQuery(query);

    manager->get(QNetworkRequest(url));
}

void ApiYandexSearch::getSuggestionsFinished(QNetworkReply *reply)
{
    QByteArray content = reply->readAll();

    QJsonParseError parseError;

    QVariant json = QJsonDocument::fromJson(content, &parseError).toVariant();
    if (Q_UNLIKELY(parseError.error)) {
        qWarning() << "ApiYandexSearch::getSuggestionsFinished():"
                   << tr("Can't parse JSON data:") << content
                   << tr(". Parser returned an error:") << parseError.errorString();
        qWarning() << "Request:" << m_lastSuggestionsRequest;
        m_lastSuggestionsRequest.clear();
        return;
    }
    QVariantList jsonList = json.toList();

    if (jsonList.size() == 0) {
            return;
    }

    QVariantList suggestions = jsonList.at(1).toList();

    QList<Consts::Shared::Suggestion> suggestionsToReturn;
    forc11 (QVariant var, suggestions) {
        Consts::Shared::Suggestion suggestion;

        // Query
        if (var.type() == QVariant::String) {
            suggestion.text = var.toString();
            suggestion.kind = Consts::Shared::Suggestion::Kind::Query;
        }
        else if (var.type() == QVariant::List) {
            QVariantList list = var.toList();

            QString kind = list.first().toString();

            // Fact
            if (kind == "fact") {
                suggestion.text = list.at(1).toString();
                suggestion.kind = Consts::Shared::Suggestion::Kind::Fact;
                suggestion.others.fact = list.at(2).toString();
            }

            // Navigation
            else if (kind == "nav") {
                suggestion.text = list.at(3).toString();
                suggestion.kind = Consts::Shared::Suggestion::Kind::Navigation;
                const QString nameOfGoToSite = QString::fromUtf8("перейти на сайт");
                if (list.at(2).toString() != nameOfGoToSite)
                    suggestion.others.linkTitle = list.at(2).toString();
            }
            else {
                continue;
            }
        }
        else {
            continue;
        }

        suggestionsToReturn.append(suggestion);
    }

    emit suggestionsReceived(m_lastSuggestionsRequest, suggestionsToReturn);
    m_lastSuggestionsRequest.clear();
}
