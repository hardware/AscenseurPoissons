#-------------------------------------------------
#
# Project created by QtCreator 2013-01-22T13:29:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHM
TEMPLATE = app


SOURCES += main.cpp\
        ui.cpp \
    accueildlg.cpp \
    manueldlg.cpp \
    seancedlg.cpp \
    statusdlg.cpp \
    synoptiquedlg.cpp \
    journaldlg.cpp \
    seance.cpp

HEADERS  += ui.h \
    accueildlg.h \
    manueldlg.h \
    seancedlg.h \
    statusdlg.h \
    synoptiquedlg.h \
    journaldlg.h \
    seance.h

FORMS    += ui.ui

RESOURCES += \
    Assets.qrc
