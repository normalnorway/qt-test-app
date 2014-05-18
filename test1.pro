CONFIG += debug
QMAKE_CXX = g++-4.8
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_DEBUG -= -g

QT	+= core network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app

SOURCES += main.cc	\
	   myobject.cc

HEADERS += myobject.h
