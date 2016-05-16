QT += core network widgets

CONFIG += c++11

TARGET = server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    client.cpp

HEADERS += \
    server.h \
    client.h

PROTOS = talkmessage.proto
include(protobuf.pri)
LIBS += -lprotobuf
