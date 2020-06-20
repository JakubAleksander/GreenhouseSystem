#-------------------------------------------------
#
# Project created by QtCreator 2020-04-29T00:03:28
#
#-------------------------------------------------

QT       += \
         core gui\
         mqtt\
         core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GreenhouseApp
TEMPLATE = app

UI_DIR += build/ui
RCC_DIR += build/rcc
MOC_DIR += build/moc
INCLUDEPATH += \
        src

CONFIG += c++11\
          debug

SOURCES += \
        src/main.cpp\
        src/mainwindow.cpp \
        src/SectionWidget/section.cpp \
        src/SectionWidget/settingsdialog.cpp \
        src/digitalclock.cpp \
        src/sectionsmanager.cpp \
        src/messenger.cpp \
        src/SectionWidget/device.cpp

HEADERS  += \
        src/SectionWidget/settingsdialog.h \
        src/mainwindow.h \
        src/SectionWidget/section.h \
        src/digitalclock.h \
        src/sectionsmanager.h \
        src/messenger.h \
        src/SectionWidget/device.h

FORMS    += \
        src/mainwindow.ui \
        src/SectionWidget/section.ui \
        src/SectionWidget/sectionsettings.ui

RESOURCES += \
        resources/resources.qrc
