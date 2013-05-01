##################################################
# Joly. Connect your web and your computer in the one place.
# Copyright (C) 2012-2013 Ivan Akulov <gxoptg@gmail.com>
#
# This file is the part of Joly.
# 
# Joly is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Joly is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Joly. If not, see <http://www.gnu.org/licenses/>.
##################################################

#-------------------------------------------------
#
# Project created by QtCreator 2011-08-03T18:19:19
#
#-------------------------------------------------

QT       += core gui webkitwidgets xml network widgets script

TARGET = jolyapp
TEMPLATE = app


SOURCES += main.cpp \
    strtools.cpp \
    ostools.cpp \
    _lineedit.cpp \
    g_messages.cpp \
    g_abstractgadget.cpp \
    board.cpp \
    consts.cpp \
    g_fastpost.cpp \
    g_globalline.cpp \
    _completer.cpp \
    settingswidget.cpp \
    ostools_executablefilesinterface.cpp \
    apivkpermissions.cpp \
    apivkdirect.cpp \
    apivkauth.cpp \
    apivk.cpp \
    ostools_appsinterface.cpp \
    _textedit.cpp \
    imgtools.cpp \
    g_fastpost_fileicon.cpp \
    g_fastpost_dropfield.cpp \
    g_fastpost_attachedfile.cpp \
    g_fastpost_attachedfilesfield.cpp \
    apivk_filesuploader.cpp \
    g_globalline_completer.cpp \
    g_globalline_completeritem.cpp \
    apitwi.cpp \
    apitwiauth.cpp \
    apitwiauth_twitterpinwidget.cpp \
    notifierbox.cpp \
    apigooglesearch.cpp \
    apiyandexsearch.cpp \
    ostools_userfilesinterface.cpp

HEADERS  += \
    strtools.h \
    ostools.h \
    _lineedit.h \
    g_messages.h \
    g_abstractgadget.h \
    consts.h \
    board.h \
    g_fastpost.h \
    g_globalline.h \
    _completer.h \
    settingswidget.h \
    ostools_executablefilesinterface.h \
    apivkpermissions.h \
    apivkdirect.h \
    apivkauth.h \
    apivk.h \
    ostools_appsinterface.h \
    _textedit.h \
    imgtools.h \
    g_fastpost_fileicon.h \
    g_fastpost_dropfield.h \
    g_fastpost_attachedfile.h \
    g_fastpost_attachedfilesfield.h \
    apivk_filesuploader.h \
    g_globalline_completer.h \
    g_globalline_completeritem.h \
    apitwi.h \
    apitwiauth.h \
    apitwiauth_twitterpinwidget.h \
    notifierbox.h \
    apigooglesearch.h \
    apiyandexsearch.h \
    ostools_userfilesinterface.h

OTHER_FILES += \
    LICENSE \
    AUTHORS

FORMS += \
    g_fastpost.ui \
    g_globalline.ui \
    settingswidget.ui \
    g_fastpost_fileicon.ui \
    g_fastpost_dropfield.ui \
    apitwiauth_twitterpinwidget.ui \
    notifierbox.ui

RESOURCES += \
    joly.qrc

QMAKE_CXXFLAGS += -std=c++0x -U__STRICT_ANSI__

INCLUDEPATH += "includes"

unix {
    INCLUDEPATH -= "includes/QJson" "includes/QJson/include"
    LIBS += -L. "libqtweetlib.so.1" -L/usr/local/lib -lqjson
}

windows {
    LIBS +=  "Libs\\qjson\\qjson0.dll" "Libs\\qttweetlib\\qtweetlib.dll"
    CODECFORTR = UTF-8
    QMAKE_CXXFLAGS += -U__STRICT_ANSI__
    DEFINES += WIN_OLD_COMPILER
}
