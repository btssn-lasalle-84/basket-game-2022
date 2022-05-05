QT       += core gui widgets sql
QT       += bluetooth
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaseDeDonnees.cpp \
    Club.cpp \
    Communication.cpp \
    Equipe.cpp \
    IHM.cpp \
    Joueur.cpp \
    Seance.cpp \
    main.cpp

HEADERS += \
    BaseDeDonnees.h \
    Club.h \
    Communication.h \
    Equipe.h \
    IHM.h \
    Joueur.h \
    Seance.h

FORMS += \
    IHM.ui

RESOURCES += \
    ressources.qrc

COPIES += bd
bd.files = basket-game.sqlite
bd.path = $$OUT_PWD/
bd.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
