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

#include "g_globalline_completer.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QScrollArea>
#include "consts.h"

#ifdef WIN_OLD_COMPILER
uint Completer::maxHeight = 10;
#endif

CompleterItem::Position::Section& operator++(CompleterItem::Position::Section &s) {
    typedef CompleterItem::Position::Section Section;

    int newValue = static_cast<int>(s) + 1;
    // TOMODIFY when adding section
    if (newValue <= static_cast<int>(Section::Commands)) { // 'Commands' may be the last value
        s = static_cast<CompleterItem::Position::Section>(newValue);
    } else {
        s = static_cast<CompleterItem::Position::Section>(0);
    }

    return s;
}

CompleterItem::Position::Section& operator--(CompleterItem::Position::Section &s) {
    typedef CompleterItem::Position::Section Section;

    int newValue = static_cast<int>(s) - 1;
    if (newValue >= 0) {
        s = static_cast<CompleterItem::Position::Section>(newValue);
    } else {
        // TOMODIFY when adding section
        s = Section::Commands; // 'Commands' may be the last value
    }

    return s;
}


Completer::Completer(QWidget *parent) :
    QScrollArea(parent), m_currentFocusPosition(CompleterItemPosition::Section::Default, 0), m_basicWidget(nullptr)
{
    setBasicWindowFlags();
    setupUi();
}

CompleterItemContent Completer::itemAt(CompleterItemPosition pos) const
{
    CompleterItem *widget = widgetAt(pos);
    if (widget)
        return widget->getContent();
    else
        return CompleterItemContent();
}

void Completer::complete() {
    setBasicDisplayParameters();
    show();
}

void Completer::clear() {
    restoreFocus();
    removeAllItems();
    hide();
}

bool Completer::setFocusAt(CompleterItemPosition pos) {
    CompleterItem *newWidget = widgetAt(pos);

    if (!newWidget) {
        return false;
    }

    Q_ASSERT(widgetAt(m_currentFocusPosition) != nullptr);
    Q_ASSERT(newWidget != nullptr);

    widgetAt(m_currentFocusPosition)->setFocused(false);
    newWidget->setFocused(true);
    m_currentFocusPosition = pos;
    return true;
}

bool Completer::hasItemAt(CompleterItemPosition pos)
{
    return !(itemAt(pos).isNull());
}

void Completer::moveFocusUp() {
    if (itemsCount() == 0)
        return;

    CompleterItemPosition newPos = m_currentFocusPosition;

    if (m_currentFocusPosition.id == 0) {
        CompleterItemPosition::Section section = newPos.section;
        do {
            --section;
        } while (ui.layoutForSection(section)->count() == 0);

        newPos.section = section;
        newPos.id = ui.layoutForSection(newPos.section)->count() - 1;
    }
    else {
        --newPos.id;
    }

    setFocusAt(newPos);
}

void Completer::moveFocusDown() {
    if (itemsCount() == 0)
        return;

    CompleterItemPosition newPos = m_currentFocusPosition;

    Q_ASSERT(ui.layoutForSection(m_currentFocusPosition.section)->count() > 0);
    if (m_currentFocusPosition.id == uint(ui.layoutForSection(m_currentFocusPosition.section)->count()) - 1) {
        CompleterItemPosition::Section section = newPos.section;
        do {
            ++section;
        } while (ui.layoutForSection(section)->count() == 0);

        newPos.section = section;
        newPos.id = 0;
    }
    else {
        ++newPos.id;
    }

    setFocusAt(newPos);
}

void Completer::restoreFocus() {
    setFocusAt(CompleterItemPosition(CompleterItemPosition::Section::Default, 0));
}

void Completer::setDefaultSection(const QList<CompleterItemContent> &items)
{
    setLayoutContent(items, ui.defaultSectionLayout.data());
}

void Completer::setSearchSuggestions(const QList<CompleterItemContent> &items)
{
    setLayoutContent(items, ui.searchSuggestionsSectionLayout.data());
}

void Completer::setLaunchedSection(const QList<CompleterItemContent> &items)
{
    setLayoutContent(items, ui.launchedSectionLayout.data());
}

void Completer::setContentDependentSection(const QList<CompleterItemContent> &items)
{
    setLayoutContent(items, ui.contentDependentSectionLayout.data());
}

void Completer::setAppsSection(const QList<CompleterItemContent> &items)
{
    setLayoutContent(items, ui.appsSectionLayout.data());
}

void Completer::setFilesSection(const QList<CompleterItemContent> &items)
{
    setLayoutContent(items, ui.filesSectionLayout.data());
}

void Completer::setCommandsSection(const QList<CompleterItemContent> &items)
{
    setLayoutContent(items, ui.commandsSectionLayout.data());
}

void Completer::setBasicWidget(QWidget *widget)
{
    m_basicWidget = widget;
//    setMaximumHeight(m_basicWidget->height() * 15);
}

// TOMODIFY when adding section
void Completer::setupUi()
{
//    setStyleSheet("Completer {background-color: white;}");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    ui.defaultSectionLayout = new QVBoxLayout;
    layout->addLayout(ui.defaultSectionLayout);
    ui.searchSuggestionsSectionLayout = new QVBoxLayout;
    layout->addLayout(ui.searchSuggestionsSectionLayout);
    ui.launchedSectionLayout = new QVBoxLayout;
    layout->addLayout(ui.launchedSectionLayout);
    ui.contentDependentSectionLayout = new QVBoxLayout;
    layout->addLayout(ui.contentDependentSectionLayout);
    ui.appsSectionLayout = new QVBoxLayout;
    layout->addLayout(ui.appsSectionLayout);
    ui.filesSectionLayout = new QVBoxLayout;
    layout->addLayout(ui.filesSectionLayout);
    ui.commandsSectionLayout = new QVBoxLayout;
    layout->addLayout(ui.commandsSectionLayout);

    m_content.setLayout(layout);

    const int heightOfTenCompleterItems = 320;
    setMaximumHeight(heightOfTenCompleterItems);
}

void Completer::setLayoutContent(const QList<CompleterItemContent> &list, QLayout *layout)
{
    Q_ASSERT(layout != 0);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Clearing layout
    while (layout->count() != 0) {
        layout->takeAt(0)->widget()->deleteLater();
    }

    // Creating CompleterItem based on CompleterItemContent
    forc11 (CompleterItemContent itemContent, list) {
        CompleterItem *item = new CompleterItem(itemContent);

        item->setFixedHeight(32);
        /* Magic number. Hope will fix soon.
         * Actually, there's the strange issue. Some completer items has height 32, but some 34. I don't know why.
         * Maybe this is because of incorrect icons scaling?
         * But nevermind. Just listen a Japan flute and relax.
         * Moreover, I can advise you to listen Roberto Cacciapaglia, Coldplay, Lenka, John Williams, The Piano Guys or smb else.
         * Also have a look at thequietplaceproject.com (not an advert, of course :)
         * Life is great, but life is short.
         * Relax :)
         */
        layout->addWidget(item);
        connect (item, SIGNAL(clicked(CompleterItem::Content)), SIGNAL(activated(CompleterItem::Content)));
        connect (item, SIGNAL(focused(CompleterItem::Content)), SLOT(ensureCompleterItemVisible(CompleterItem::Content)));
    }

    restoreFocus();
}

void Completer::setBasicDisplayParameters()
{
    QPoint topLeftCorner = m_basicWidget->mapToGlobal(QPoint(0,0));
    int basicWidgetHeight = m_basicWidget->height();
    int distance = topLeftCorner.y() + basicWidgetHeight + 0;
    move(topLeftCorner.x(), distance);

    if(this->widget() == 0) {
        setWidget(&m_content);
        setWidgetResizable(true);
    }

    int width = m_basicWidget->width();
    setFixedWidth(width);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

// TOMODIFY when adding section
void Completer::removeAllItems()
{
    while(ui.defaultSectionLayout->count() != 0)
        ui.defaultSectionLayout->takeAt(0)->widget()->deleteLater();

    while(ui.searchSuggestionsSectionLayout->count() != 0)
        ui.searchSuggestionsSectionLayout->takeAt(0)->widget()->deleteLater();

    while(ui.launchedSectionLayout->count() != 0)
        ui.launchedSectionLayout->takeAt(0)->widget()->deleteLater();

    while(ui.contentDependentSectionLayout->count() != 0)
        ui.contentDependentSectionLayout->takeAt(0)->widget()->deleteLater();

    while(ui.appsSectionLayout->count() != 0)
        ui.appsSectionLayout->takeAt(0)->widget()->deleteLater();

    while(ui.filesSectionLayout->count() != 0)
        ui.filesSectionLayout->takeAt(0)->widget()->deleteLater();

    while(ui.commandsSectionLayout->count() != 0)
        ui.commandsSectionLayout->takeAt(0)->widget()->deleteLater();
}

CompleterItem *Completer::widgetAt(CompleterItemPosition pos) const
{
    if (pos.id < uint(ui.layoutForSection(pos.section)->count())) {
        return qobject_cast<CompleterItem *>(ui.layoutForSection(pos.section)->itemAt(pos.id)->widget());
    } else {
        return nullptr;
    }
}

void Completer::enterEvent(QEvent *)
{
    widgetAt(m_currentFocusPosition)->setFocused(false);
}

void Completer::leaveEvent(QEvent *)
{
    if (widgetAt(m_currentFocusPosition))
        widgetAt(m_currentFocusPosition)->setFocused(true);
}

void Completer::ensureCompleterItemVisible(CompleterItem::Content itemContent)
{
    CompleterItem *item = widgetAt(itemContent.pos);
    if (!item)
        return;

    QPoint point = item->pos();
    ensureVisible(point.x(), point.y());
}
