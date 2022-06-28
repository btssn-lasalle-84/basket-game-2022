/*        
Projets : b4sket-game

                    FICHIER DE DECLARATION 


Auteur : MEM
Date: 10/06/22
Version : 3.0
*/
#ifndef B4SKET_GAME_H
#define B4SKET_GAME_H

#include <Arduino.h>
#include <BluetoothSerial.h>

#define VITESSE_SERIE 9600
#define CAPTEUR1 23
#define CAPTEUR2 18
#define CAPTEUR3 16
#define ALLUMER HIGH
#define ETEINDRE LOW
#define ATTENTE 25
#define INITIALISATION 3000
#define VALIDE true
#define NONVALIDE false
#define DEBUG


void initInfrarouge(void);
bool trameValide(String trame);

#endif