QT += testlib\
    gui\
    widgets\
    mqtt\
    core

CONFIG += qt warn_on depend_includepath testcase

TARGET = TestGreenhouseApp

TEMPLATE = app

GREENHOUSEAPP_PATH = ../../GreenhouseApp/src

SOURCES += \ 
    testsection.cpp \
    $$GREENHOUSEAPP_PATH/SectionWidget/section.cpp \
    $$GREENHOUSEAPP_PATH/SectionWidget/device.cpp \
    $$GREENHOUSEAPP_PATH/SectionWidget/settingsdialog.cpp \
    $$GREENHOUSEAPP_PATH/messenger.cpp
HEADERS += \
    testsection.h \
    $$GREENHOUSEAPP_PATH/SectionWidget/section.h \
    $$GREENHOUSEAPP_PATH/SectionWidget/device.h \
    $$GREENHOUSEAPP_PATH/SectionWidget/settingsdialog.h \
    $$GREENHOUSEAPP_PATH/messenger.h

FORMS += \
    $$GREENHOUSEAPP_PATH/SectionWidget/section.ui \
    $$GREENHOUSEAPP_PATH/SectionWidget/sectionsettings.ui
