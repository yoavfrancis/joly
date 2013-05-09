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

#ifndef G_GLOBALLINE_COMPLETER_H
#define G_GLOBALLINE_COMPLETER_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QMap>
#include "g_globalline_completeritem.h"
#include "consts.h"

typedef CompleterItem::Content CompleterItemContent;
typedef CompleterItem::Position CompleterItemPosition;

class Completer : public QScrollArea
{
    Q_OBJECT
public:

    explicit Completer(QWidget *parent = 0);
//    explicit Completer(const QList<CompleterItemContent> &list, QWidget *parent = 0);

    // TOMODIFY when adding section
    inline uint itemsCount() const
    {
        return ui.defaultSectionLayout->count() +
                ui.searchSuggestionsSectionLayout->count() +
                ui.launchedSectionLayout->count() +
                ui.contentDependentSectionLayout->count() +
                ui.appsSectionLayout->count() +
                ui.filesSectionLayout->count() +
                ui.commandsSectionLayout->count();
    }
    CompleterItemContent itemAt(CompleterItemPosition pos) const;

    bool setFocusAt(CompleterItemPosition pos);
    inline CompleterItemContent getFocusedItemContent() const { return itemAt(m_currentFocusPosition); }
    bool hasItemAt(CompleterItemPosition pos);

    // TOMODIFY when adding section (add the function)
    void setDefaultSection(const QList<CompleterItemContent> &items);
    void setSearchSuggestions(const QList<CompleterItemContent> &items);
    void setLaunchedSection(const QList<CompleterItemContent> &items);
    void setContentDependentSection(const QList<CompleterItemContent> &items);
    void setAppsSection(const QList<CompleterItemContent> &items);
    void setFilesSection(const QList<CompleterItemContent> &items);
    void setCommandsSection(const QList<CompleterItemContent> &items);

    void setBasicWidget(QWidget *widget);
    inline QWidget* getBasicWidget() const { return m_basicWidget; }

signals:
    void activated(const CompleterItem::Content &content);

public slots:
    void complete();
    void clear();
    void moveFocusUp();
    void moveFocusDown();
    void restoreFocus();
    inline void updateHeight() {
        if (itemsCount() < maxHeight)
            resize(width(), getNewHeight());
//        qDebug() << sizeHint().height();
    }


protected:
    void setupUi();
    void setLayoutContent(const QList<CompleterItemContent> &list, QLayout *layout);
    void setBasicDisplayParameters();
    void removeAllItems();
    inline void setBasicWindowFlags() {
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setAttribute(Qt::WA_ShowWithoutActivating);
    }

    inline int getNewHeight() const {
        CompleterItem *firstCompleterItem = widgetAt(CompleterItemPosition(CompleterItemPosition::Section::Default, 0));
        return firstCompleterItem->sizeHint().height() * qMin(itemsCount(), maxHeight) + 2;
    }

    CompleterItem* widgetAt(CompleterItemPosition pos) const;

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

protected slots:
    void ensureCompleterItemVisible(CompleterItem::Content itemContent);

private:
    CompleterItem::Position m_currentFocusPosition;
    struct _ui {
        // TOMODIFY when adding section
        QPointer<QVBoxLayout> defaultSectionLayout;
        QPointer<QVBoxLayout> searchSuggestionsSectionLayout;
        QPointer<QVBoxLayout> launchedSectionLayout;
        QPointer<QVBoxLayout> contentDependentSectionLayout;
        QPointer<QVBoxLayout> appsSectionLayout;
        QPointer<QVBoxLayout> filesSectionLayout;
        QPointer<QVBoxLayout> commandsSectionLayout;

        // TOMODIFY when adding section
        inline QPointer<QVBoxLayout> layoutForSection(CompleterItem::Position::Section section) const {
            typedef CompleterItem::Position::Section Section;
            switch (section) {
            case Section::Default:
                return defaultSectionLayout;
                break;
            case Section::SearchSuggestions:
                return searchSuggestionsSectionLayout;
                break;
            case Section::Launched:
                return launchedSectionLayout;
                break;
            case Section::ContentDependent:
                return contentDependentSectionLayout;
                break;
            case Section::Apps:
                return appsSectionLayout;
                break;
            case Section::Files:
                return filesSectionLayout;
                break;
            case Section::Commands:
                return commandsSectionLayout;
                break;
            default:
                Q_ASSERT_X(false, "_m_actions::actionsForSection", "unaccounted parameter of switch");
                return *(new QPointer<QVBoxLayout>(nullptr));
            }
        }
    } ui;

    QWidget *m_basicWidget;
    QWidget m_content;

#ifdef WIN_OLD_COMPILER
    static uint maxHeight;
#else
    const uint maxHeight = 10;
#endif
};

#endif // G_GLOBALLINE_COMPLETER_H
