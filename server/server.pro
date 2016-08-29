QT += core network widgets sql

CONFIG += c++11

TARGET = server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    client.cpp \
    room.cpp

HEADERS += \
    server.h \
    client.h \
    room.h

PROTOS = talkmessage.proto
include(protobuf.pri)
LIBS += -lprotobuf
