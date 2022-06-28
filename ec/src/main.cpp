/*
Projets : b4sket-game

                                    Programme b4sket-game

                                   
Auteur : MEM
Date: 10/06/22
Version : 3.0                       
 */

#include <Arduino.h>
#include <Wire.h>
#include <SSD1306Wire.h>  
#include <BluetoothSerial.h>
#include "afficheroled.h"
#include "b4sket_game.h"

////////////////////////////////////////////////////////////////////////

SSD1306Wire afficheuroled(ADRESSE_OLED, SDA, SCL);
BluetoothSerial moduleBluetooth;

////////////////////////////////////////////////////////////////////////

String nomModuleBluetooth = "B4SKET_etat";
extern String entete_de_la_trame;
extern String delimiteur_de_fin;
extern String TypeChamps;
extern String ValeurChamps;
extern String separateur_de_champ;
String trameAdecoupee = "";


////////////////////////////////////////////////////////////////////////

void setup()
{
	
    Serial.begin(VITESSE_SERIE);                                // vitesse liaison serie
    moduleBluetooth.begin("B4SKET_etat");

	afficheuroled.init();                                       // initialise ecran oled
	afficheuroled.flipScreenVertically();                       // le sens du texte
	afficheuroled.setFont(ArialMT_Plain_16);                    // taille et police de l'écriture

	afficheuroled.clear();                                      // rafraichissement de l'ecran

    afficheuroled.drawString(10,0,"B4SKETGAME");                // position du texte 
    afficheuroled.drawString(16,32,"Chargement...");            // position du texte 
    afficheuroled.display();                                    // affiche le texte 
    delay(INITIALISATION);
    afficheuroled.clear();                                      // rafraichissement de l'ecran
    afficheuroled.drawString(10,0,"B4SKETGAME");                // position du texte 
    afficheuroled.drawString(0,32,"Démarrer la partie");        // position du texte 
    afficheuroled.setFont(ArialMT_Plain_10);                    // police du texte
    afficheuroled.drawString(6,48,"VOUS POUVEZ TIRER !!");      // position du texte 
    afficheuroled.display();                                    // affiche le texte 
    afficheuroled.setFont(ArialMT_Plain_16);                    // police du texte
}

////////////////////////////////////////////////////////////////////////

void loop()
{
    if (moduleBluetooth.available() > 0)
    {
        //String trame_recue= moduleBluetooth.readString();
        String trame_recue= moduleBluetooth.readStringUntil('\r');
        if(trameValide(trame_recue))
        {
            trameAdecoupee = trame_recue;
            trameAdecoupee = trameAdecoupee.substring(entete_de_la_trame.length(),(trameAdecoupee.length()-delimiteur_de_fin.length()));
            Serial.println(trameAdecoupee);
            if(trame_recue.indexOf("STT") != -1)
            {
                tour = 0; // les rouges
                encours = true; 
                Serial.println("Démarrage partie");
            }
            else if(trame_recue.indexOf("STP") != -1)
            {
                encours = false; 
                Serial.println("Arrêt partie");
            }
        }
    }
         
    ///////////////////////////Module Infrarouge 1///////////////////////////

    etatCapteur = digitalRead(CAPTEUR1);//lecture du capteur.
    
    if (etatCapteur == ALLUMER) //si quelquechose est detecte.
    {
        etat = 0 ;// etat du capteur    
        if (etat != preEtat )    
        {
            panier1++ ;
            
            Serial.print("Panier 1 marqué : ");
            Serial.println(panier1);

            afficheuroled.clear();
            afficheuroled.drawString(10,0,"B4SKETGAME");

            String basket = "Panier 1 =" + String(panier1);
                        afficheuroled.drawString(26,32,basket);
                        afficheuroled.display();

            if(encours)
            {
                Serial.println("Envoi trame panier1");
                if(tour % 2 == 0)
                {
                    String message = "$basket;P;1;R;\r"; 
                    moduleBluetooth.print(message);
                }
                else
                {
                    String message = "$basket;P;1;J;\r"; 
                    moduleBluetooth.print(message);
                }
                ++tour;
            }
    
            delay(ATTENTE);		 
        } 

    }
    else
    {
        etat = 1;// etat du capteur 
    }
    delay(ATTENTE) ;
    preEtat = etat ; //etat precedent prend les valeurs de l'etat actuel.
 
    ///////////////////////////Module Infrarouge 2///////////////////////////

    etatCapteur2 = digitalRead(CAPTEUR2);//lecture du capteur.

    if (etatCapteur2 == ALLUMER) //si quelquechose est detecte.
    {
        etat2 = 0 ;// etat du capteur  

        if (etat2 != preEtat2 )    
        {
            panier2++;

            Serial.print("Panier 2 marqué : ");
            Serial.println(panier2);
            
            afficheuroled.clear();
            afficheuroled.drawString(10,0,"B4SKETGAME");

            String basket2 = "Panier 2 =" + String(panier2);
                        afficheuroled.drawString(26,32,basket2);
                        afficheuroled.display();

            if(encours)
            {
                Serial.println("Envoi trame panier2");
                if(tour % 2 == 0)
                {
                    String message = "$basket;P;2;R;\r"; 
                    moduleBluetooth.print(message);
                }
                else
                {
                    String message = "$basket;P;2;J;\r"; 
                    moduleBluetooth.print(message);
                }
                ++tour;
            }
            delay(ATTENTE);	
        }
    }
    else
    {
        etat2 = 1;// etat du capteur 
    }
    delay(ATTENTE) ;
    preEtat2 = etat2 ; //etat precedent prend les valeurs de l'etat actuel.

///////////////////////////Module Infrarouge 3///////////////////////////

    etatCapteur3 = digitalRead(CAPTEUR3);//lecture du capteur.

    if (etatCapteur3 == ALLUMER) //si quelquechose est detecte.
    {
        etat3 = 0 ;// etat du capteur  

        if (etat3 != preEtat3 )    
        {
            panier3++;

            Serial.print("Panier 3 marqué : ");
            Serial.println(panier3);
            
            afficheuroled.clear();
            afficheuroled.drawString(10,0,"B4SKETGAME");

            String basket3 = "Panier 3 =" + String(panier3);
                        afficheuroled.drawString(26,32,basket3);
                        afficheuroled.display();

            if(encours)
            {
                Serial.println("Envoi trame panier3");
                if(tour % 2 == 0)
                {
                    String message = "$basket;P;3;R;\r"; 
                    moduleBluetooth.print(message);
                }
                else
                {
                    String message = "$basket;P;3;J;\r"; 
                    moduleBluetooth.print(message);
                }
                ++tour;
            }
            delay(ATTENTE);	
        }
    }
    else
    {
        etat3 = 1;// etat du capteur 
    }
    delay(ATTENTE) ;
    preEtat3 = etat3 ; //etat precedent prend les valeurs de l'etat actuel.
}
