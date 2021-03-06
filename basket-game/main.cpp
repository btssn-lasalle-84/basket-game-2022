#include "IHM.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application basket-game
 * @author
 * @version 1.1
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    IHM          w;

    w.show();

    return a.exec();
}
