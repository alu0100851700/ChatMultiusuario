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

unix {# Esta configuración es específica de Linux y UNIX
    # Variables
    #
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    BINDIR  = $$PREFIX/bin
    DATADIR = $$PREFIX/share
    CONFDIR = /etc
    isEmpty(VARDIR) {
        VARDIR  = /var/lib/$${TARGET}
    }

    # Install
    #
    INSTALLS += target desktop icon32

    ## Instalar ejecutable
    target.path = $$BINDIR


    ## Instalar acceso directo en el menú del escritorio
    desktop.path = $$DATADIR/applications
    desktop.files += talk.desktop

    ## Instalar icono de aplicación
    icon32.path = $$DATADIR/icons/hicolor/32x32/apps
    icon32.files += icono-chat.png

}
