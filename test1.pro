# Q: how to check for non-android build?
!android_app {
  message ("not android")
}
# Q: can pass from command line / environment?
#linux {
#    QMAKE_CXX = g++-4.8
#    QMAKE_CXXFLAGS += -std=c++11
#    QMAKE_CXXFLAGS_DEBUG -= -g
#}
# !!!

#CONFIG += c++11
CONFIG += debug

#CONFIG += mobility
#MOBILITY += systeminfo

QT += core network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app

SOURCES += main.cc	\
	   myobject.cc	\
	   mainwindow.cc

HEADERS += myobject.h	\
	   mainwindow.h

RESOURCES = resources.qrc


## Android build
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
