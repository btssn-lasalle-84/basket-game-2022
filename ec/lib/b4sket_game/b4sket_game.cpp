/*    
Projets : b4sket-game    
                    FICHIER DE DEFINITION



Auteur : MEM
Date: 10/06/22
Version : 3.0
*/ 
////////////////////////////////////////////////////////////////////////////////////
#include "b4sket_game.h"
#include <Arduino.h>
////////////////////////////////////////////////////////////////////////////////////

String entete_de_la_trame= "$basket;";
String separateur_de_champ = ";";
String delimiteur_de_fin= "\r";
String TypeChamps[]={"Aquittement_Bluetooth :"};
String ValeurChamps[]={"Verification_de_la_connexion :"};

////////////////////////////////////////////////////////////////////////////////////

void initInfrarouge(){
     
    pinMode(CAPTEUR1, INPUT); //la broche du capteur est mise en entree.
    pinMode(CAPTEUR2, INPUT); //la broche du capteur 2 est mise en entree.
}

bool trameValide(String trame){
    bool trameValide = NONVALIDE;
    if(trame.startsWith(entete_de_la_trame)) trameValide =VALIDE;
    return  trameValide;
}