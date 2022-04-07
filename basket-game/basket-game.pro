QT       += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IHM.cpp \
    Joueur.cpp \
    Seance.cpp \
    main.cpp

HEADERS += \
    IHM.h \
    Joueur.h \
    Seance.h

FORMS += \
    IHM.ui

RESOURCES += \
    ressources.qrc

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
