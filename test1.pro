# will fuck up android build
#linux {
#    QMAKE_CXX = g++-4.8
#    QMAKE_CXXFLAGS += -std=c++11
#    QMAKE_CXXFLAGS_DEBUG -= -g
#}

CONFIG += debug
CONFIG += mobility

QT += core network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app

SOURCES += main.cc	\
	   myobject.cc

HEADERS += myobject.h

RESOURCES = resources.qrc


## Android build
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
