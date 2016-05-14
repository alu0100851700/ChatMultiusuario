#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T11:30:35
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = talk-gui
TEMPLATE = app
CONFIG += openssl-linked


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    settingsdialog.ui
