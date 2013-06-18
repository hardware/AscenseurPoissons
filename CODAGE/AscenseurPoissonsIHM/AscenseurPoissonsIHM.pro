HEADERS += \
    synoptiquedlg.h \
    statutsdlg.h \
    seancedlg.h \
    manueldlg.h \
    journaldlg.h \
    ihm.h \
    accueildlg.h \
    seance.h \
    interfacecan.h \
    pompe.h \
    centralehydraulique.h \
    vanneattrait.h \
    cageascenseur.h \
    grille.h \
    capteurs.h \
    Canproex.h \
    Canpcex.h \
    Candefex.h \
    ascpdef.h \
    interfacecandlg.h \
    journalevenements.h \
    ascpihmdef.h

SOURCES += \
    synoptiquedlg.cpp \
    statutsdlg.cpp \
    seancedlg.cpp \
    manueldlg.cpp \
    main.cpp \
    journaldlg.cpp \
    ihm.cpp \
    accueildlg.cpp \
    seance.cpp \
    interfacecan.cpp \
    pompe.cpp \
    centralehydraulique.cpp \
    vanneattrait.cpp \
    cageascenseur.cpp \
    grille.cpp \
    capteurs.cpp \
    interfacecandlg.cpp \
    journalevenements.cpp

RESOURCES += \
    assets.qrc

win32: LIBS += -L$$PWD/ -lNSICANEX

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
