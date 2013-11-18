COMP_Location = C://Qt//Comp                            #location of 3rd party (ish) components

QT += qml network serialport

CONFIG   += console

TEMPLATE = app
CONFIG   -= app_bundle


HEADERS += \
    topclass.h \
    $${COMP_Location}//simplecrypt.h

SOURCES += \
    topclass.cpp\
    $${COMP_Location}//simplecrypt.cpp \
    main.cpp

INCLUDEPATH +=$${COMP_Location}


OTHER_FILES += \
    ../AutoHotkey/HAP_ahk.ahk
include($${COMP_Location}/qtservice/src/qtservice.pri)

Debug: DEFINES+= BUILDASNONSERVER



