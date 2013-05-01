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

#ifndef CONST_H
#define CONST_H

class QString;
#include "ostools.h"

namespace Consts
{
    const QString writePath = "resources/";

    namespace Gadgets {
        namespace GlobalLine {
            const QString name = "GlobalLine";
        }

        namespace Messages {
            const QString name = "Messages";
        }

        namespace FastPost {
            const QString name = "FastPost";
        }
    }

    namespace SocNetworks {
        namespace VK {
            const QString name = "VK";

            inline QString imUrl() {
                return "http://vk.com/im";
            }
        }

        namespace GPlus {
            const QString name = "Google Plus";

            inline QString imUrl() {
                return "";
            }
        }

        namespace GMail {
            const QString name = "GMail";

            inline QString imUrl() {
                return "https://mail.google.com/mail";
            }
        }

        namespace GReader {
            const QString name = "Google Reader";

            inline QString imUrl() {
                return "";
            }
        }

        namespace Facebook {
            const QString name = "Facebook";

            inline QString imUrl() {
                return "";
            }
        }

        namespace Twitter {
            const QString name =  "Twitter";

            inline QString imUrl() {
                return "";
            }
        }
    }

    namespace Colors {
        const QString light = "#ffffff";

        const QString jolly = "#2f6dff";
        const QString jollyLighter = "#3b7df9";
        const QString jollyTwiceLighter = "#4b8df9";
        const QString jollyLightest = "#7ca2fd";

        const QString lightestGrey = "#e5e5e5";
        const QString lighterGrey = "#a3a3a3";
        const QString grey = "#6d6d6d";
        const QString darkerGrey = "#515151";

        const QString dark = "#000000";
    }

    namespace Shared {
        struct Suggestion {
#ifdef WIN_OLD_COMPILER
            enum Kind {
#else
            enum class Kind {
#endif
                Query, Navigation, Fact
            };

            QString text;
            Kind kind;
            struct _others {
                QString linkTitle;
                QString fact;
            } others;
        };
    }
    const QString css = "\
* {\n\
}\n\
\n\
G_AbstractGadget {\n\
    border: 1px solid #333333;\n\
}\n\
\n\
QPushButton {\n\
    border: 1px solid #999999;\n\
    background-color: #c5c5c5;\n\
    padding: 5;\n\
}\n\
\n\
QPushButton:checked {\n\
    background-color: #333333;\n\
    color: #dddddd;\n\
    border-color: black;\n\
}\n\
\n\
QPushButton[mainButton=true] {\n\
    background-color: #4b8df9;\n\
}\n\
\n\
QPushButton:hover {\n\
    background-color: #b0b0b0;\n\
}\n\
\n\
QPushButton[mainButton=true]:hover {\n\
    background-color: #3b7df9;\n\
}\n\
\n\
QPushButton:checked:hover {\n\
    background-color: #222222;\n\
}\n\
\n\
QPushButton:pressed {\n\
    background-color: #a0a0a0;\n\
}\n\
\n\
QPushButton[mainButton=true]:pressed {\n\
    background-color: #2f6dff;\n\
}\n\
\n\
QPushButton:checked:pressed {\n\
    background-color: #111111;\n\
}\n\
\n\
QPushButton:focus {\n\
    border: 1px solid #222222;\n\
}\n\
\n\
QPushButton:!active {\n\
    border: 1px solid #aaaaaa;\n\
    background-color: #eeeeee;\n\
}\n\
\n\
QPushButton:checked:!active {\n\
    background-color: #666666;\n\
    color: #dddddd;\n\
}\n\
\n\
QPushButton:!active:hover {\n\
    background-color: #dddddd;\n\
}\n\
\n\
QPushButton:checked:!active:hover {\n\
    background-color: #444444;\n\
}\n\
\n\
QPushButton:!active:disabled {\n\
    background-color: white;\n\
}\n\
\n\
QPushButton:disabled {\n\
    background-color: white;\n\
    border: 1px solid #aaaaaa;\n\
}\n\
\n\
QLineEdit, QTextEdit {\n\
    border: 1px solid #4b8df9;\n\
}\n\
\n\
QLineEdit:hover, QTextEdit:hover {\n\
    border: 1px solid #3b7df9;\n\
}\n\
\n\
QLineEdit:focus, QTextEdit:focus {\n\
    border: 1px solid #2f6dff;\n\
}\n\
\n\
QLineEdit:!active, QTextEdit:!active {\n\
    border: 1px solid #aaaaaa;\n\
}\n\
\n\
QLineEdit:disabled, QTextEdit:disabled {\n\
    border: 1px solid #aaaaaa;\n\
}\n\
\n\
QScrollBar:vertical {\n\
    border: 0;\n\
    background: white;\n\
    width: 3px;\n\
}\n\
\n\
QScrollBar:horizontal {\n\
    border: 0;\n\
    background: white;\n\
    height: 3px;\n\
}\n\
\n\
QScrollBar::handle { \n\
    background: black;\n\
}\n\
\n\
QScrollBar::add-line {\n\
    width: 0px;\n\
    height: 0px;\n\
    border: 0px;\n\
}\n\
\n\
QScrollBar::sub-line {\n\
    width: 0px;\n\
    height: 0px;\n\
    border: 0px;\n\
}\n\
\n\
Completer {\n\
    background-color: white;\n\
}\n\
";
}

#ifdef WIN_OLD_COMPILER
#define forc11(x,y) foreach (x, y)
#else
#define forc11(x,y) for (x : y)
#endif

#ifdef WIN_OLD_COMPILER
#define nullptr 0
#endif

#endif // CONST_H
