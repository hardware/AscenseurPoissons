#-------------------------------------------------
#
# Project created by QtCreator 2013-06-12T14:38:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = AscenseurPoissonsConsole
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    interfacecan.cpp \
    interfacecandlg.cpp

HEADERS += \
    interfacecan.h \
    Canproex.h \
    Canpcex.h \
    Candefex.h \
    types.h \
    interfacecandlg.h \
    typesInterfaceLogicielle.h



win32: LIBS += -L$$PWD/ -lNSICANEX

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
