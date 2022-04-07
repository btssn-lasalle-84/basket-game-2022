QT       += core gui widgets sql

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Seance.cpp \
    Joueur.cpp \
    basededonnees.cpp \
    main.cpp \
    ihm.cpp

HEADERS += \
    Seance.h \
    Joueur.h \
    basededonnees.h \
    ihm.h

FORMS += \
    ihm.ui

RESOURCES += \
    ressources.qrc

COPIES += bd
bd.files = basket-game.sqlite
bd.path = $$OUT_PWD/
bd.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
