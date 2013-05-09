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

#ifndef G_GLOBALLINE_COMPLETERITEM_H
#define G_GLOBALLINE_COMPLETERITEM_H

#include <QWidget>
#include <QPointer>
#include <QLabel>
#include <QFrame>

class CompleterItem : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(bool focused READ isFocused WRITE setFocused)
public:
    struct Content;
    struct Position;

    explicit CompleterItem(Position pos, QWidget *parent = 0);
    explicit CompleterItem(QPixmap pixmap, QString text, Position pos, QWidget *parent = 0);
    explicit CompleterItem(Content content, QWidget *parent = 0);

    inline QPixmap getPixmap() { return *(ui.pixmap->pixmap()); }
    inline void setPixmap(const QPixmap &pixmap) { ui.pixmap->setPixmap(pixmap); }
    inline QString getText() { return ui.text->text(); }
    inline void setText(const QString &text) { ui.text->setText(text); }
    inline bool isFocused() { return m_isFocused; }
    inline void setFocused(bool focused)
    {
        m_isFocused = focused;
        restoreBackgroundColor();
        if (focused)
            emit this->focused(getContent());
    }

    inline Content getContent() {
        Content c;
        c.pixmap = *(ui.pixmap->pixmap());
        c.text = ui.text->text();
        c.pos = m_pos;
        return c;
    }

    struct Position {
#ifdef WIN_OLD_COMPILER
        enum Section {
#else
        enum class Section {
#endif
            // TOMODIFY when adding section
            Default, SearchSuggestions, Launched, ContentDependent, Apps, Files, Commands
        };

        Position(Section s, uint i) : section(s), id(i) { }

        Section section;
        uint id;

        bool operator ==(const Position &other) {
            return (section == other.section && id == other.id);
        }
    };

    struct Content {
        Content(QPixmap pi = QPixmap(), QString t = QString(), Position po = Position(Position::Section::Default, 0))
            : pixmap (pi), text(t), pos(po) {}
        QPixmap pixmap;
        QString text;

        Position pos;

        bool isNull() { return text.isNull(); }
    };

signals:
    void focused(CompleterItem::Content content);
    void clicked(CompleterItem::Content content);

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void restoreBackgroundColor();
    void setupUi();
    void setDefaultColors();
    void setBackgroundColor(QColor color);

    inline void setContent(Content content) {
        ui.pixmap->setPixmap(content.pixmap);
        ui.text->setText(content.text);
        m_pos = content.pos;
    }

private:
    bool m_isFocused;
    Position m_pos;
    struct _ui {
        QPointer<QLabel> text;
        QPointer<QLabel> pixmap;
    } ui;
    struct _colors {
        QColor basic;
        QColor hover;
        QColor focus;
        QColor active;
    } m_colors;
};

#endif // G_GLOBALLINE_COMPLETERITEM_H
