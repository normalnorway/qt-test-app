#!/bin/sh -e

QMAKE=/opt/qt/5.2.1/android_armv7/bin/qmake

# Setup environment
#export PATH=$PATH:/opt/android/jdk/bin
#export JAVA_HOME=/opt/android/jdk

rm Makefile.android
if [ ! -e Makefile.android ]; then
    # Q: debug/release build?
    $QMAKE -o Makefile.android
fi

make="make -f Makefile.android"

$make clean
$make
$make install INSTALL_ROOT=build/android

androiddeployqt --debug --input *.json --output build/android/

# --deployment bundled|ministro|debug

# List built packages
ls -1 build/android/bin/QtApp*.apk
