#-------------------------------------------------
#
# Project created by QtCreator 2017-09-28T07:37:26
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FIRGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
HEADERS += \
    ../../include/fir.h \
    ../../include/fir-impl.h

INCLUDEPATH += ../../include
CONFIG += c++11
DEFINES += QCUSTOMPLOT_USE_OPENGL
