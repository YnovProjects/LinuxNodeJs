QT += core network widgets testlib
QT -= gui

CONFIG += c++11

TARGET = test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    serveur.cpp

HEADERS += \
    serveur.h
