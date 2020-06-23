QT += testlib
QT += gui
QT += widgets
QT += mqtt
QT += core

CONFIG += qt warn_on depend_includepath testcase

TARGET = TestGreenhouseApp

TEMPLATE = app

GREENHOUSE_APP_PATH = "../../GreenhouseApp/src"

SOURCES += \ 
    testsection.cpp \
    ../../GreenhouseApp/src/SectionWidget/section.cpp \
    ../../GreenhouseApp/src/SectionWidget/device.cpp \
    ../../GreenhouseApp/src/SectionWidget/settingsdialog.cpp \
    ../../GreenhouseApp/src/messenger.cpp
HEADERS += \
    testsection.h \
    ../../GreenhouseApp/src/SectionWidget/section.h \
    ../../GreenhouseApp/src/SectionWidget/device.h \
    ../../GreenhouseApp/src/SectionWidget/settingsdialog.h \
    ../../GreenhouseApp/src/messenger.h

FORMS += \
    ../../GreenhouseApp/src/SectionWidget/section.ui \
    ../../GreenhouseApp/src/SectionWidget/sectionsettings.ui
