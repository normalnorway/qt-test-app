#-------------------------------------------------
#
# Project created by QtCreator 2014-05-13T23:57:28
#
#-------------------------------------------------

# Added by torkel
QMAKE_CXXFLAGS += -std=c++11

QT       += core network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app


SOURCES += main.cc\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

