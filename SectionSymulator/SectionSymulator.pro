#-------------------------------------------------
#
# Project created by QtCreator 2019-09-14T17:48:01
#
#-------------------------------------------------

QT       += \
         core gui\
         mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SectionSymulator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11


UI_DIR += build/ui
RCC_DIR += build/rcc
MOC_DIR += build/moc

INCLUDEPATH += \
  src \
  src/mqtt
  
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mqtt/mqttclient.cpp

HEADERS += \
    src/mainwindow.h \
    src/mqtt/mqttclient.h

FORMS += \
    src/ui/mainwindow.ui
	
macos {
  OBJECTS_DIR += build/o/macos
  QMAKE_LIBDIR += 
}

linux-g++ {
  QMAKE_LIBDIR += 
  OBJECTS_DIR += build/o/linux
}

linux-g++-64 {
  QMAKE_LIBDIR += 
  OBJECTS_DIR += build/o/linux64
}

win32 {
  QMAKE_LIBDIR += 
  OBJECTS_DIR += build/o/win32
}
