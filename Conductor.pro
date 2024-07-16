#-------------------------------------------------
#
# Project created by QtCreator 2024-07-04T09:33:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Conductor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

LIBS += -lparsec-mac-qt5
LIBS += -lparsec-mic
LIBS += -lparsec-mac
LIBS += -lparsec-base


INCLUDEPATH +=/usr/include/parsec-qt5
INCLUDEPATH +=/usr/include/parsec
INCLUDEPATH +=/usr/include/c++/6
