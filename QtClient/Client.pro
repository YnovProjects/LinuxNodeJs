QT += core network widgets testlib
QT -= gui

CONFIG += c++11

TARGET = client
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    client.cpp

HEADERS += \
    client.h
