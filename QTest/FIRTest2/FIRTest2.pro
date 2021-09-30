QT += core
QT -= gui

CONFIG += c++11

TARGET = FIRTest2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    ../../include/fir.h \
    ../../include/fir-impl.h

INCLUDEPATH += ../../include


