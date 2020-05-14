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

TARGET = GreenhouseSystem
TEMPLATE = app

UI_DIR += build/ui
RCC_DIR += build/rcc
MOC_DIR += build/moc
INCLUDEPATH += \
  src

CONFIG += c++11

SOURCES += \
        src/main.cpp\
        src/mainwindow.cpp \
        src/SectionWidget/section.cpp \
    src/SectionWidget/sectionsettings.cpp

HEADERS  += \
        src/mainwindow.h \
        src/SectionWidget/section.h \
    src/SectionWidget/sectionsettings.h

FORMS    += \
        src/mainwindow.ui \
        src/SectionWidget/section.ui \
    src/SectionWidget/sectionsettings.ui

RESOURCES += \
    resources/resources.qrc

