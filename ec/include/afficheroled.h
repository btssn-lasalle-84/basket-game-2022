/*        
Projets : b4sket-game

                    FICHIER DE DECLARATION



Auteur : MEM
Date: 10/06/22
Version : 3.0
*/

#ifndef AFFICHEUROLED_H
#define AFFICHEUROLED_H

#define SDA  4  //ECRAN OLED    
#define SCL  17 //ECRAN OLED 

#define ADRESSE_OLED 0x3c

////////////////////// VARIABLES ////////////////////////////
int etatCapteur = 0; // etat de la sortie du capteur
int etatCapteur2 = 0; // etat de la sortie du capteur2
int etatCapteur3 = 0; // etat de la sortie du capteur2

int panier1 = 0 ;   // Nombre de panier 
int panier2 = 0 ;   // Nombre de panier 2
int panier3 = 0 ;   // Nombre de panier 2
int tour = 0;

bool etat = 0; //etat du capteur.
bool preEtat = 0; //etat précedent du capteur.
bool etat2 = 0; //etat du capteur 2.
bool preEtat2 = 0; //etat précedent du capteur 2.
bool etat3 = 0; //etat du capteur 3.
bool preEtat3 = 0; //etat précedent du capteur 3.
bool encours = false;



#endif