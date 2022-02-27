--- LDD (langage de définition de données)

--- Supprime les tables

DROP TABLE IF EXISTS Manche;
DROP TABLE IF EXISTS Partie;
DROP TABLE IF EXISTS Rencontre;
DROP TABLE IF EXISTS Equipe;
DROP TABLE IF EXISTS Joueur;
DROP TABLE IF EXISTS Club;

--- Création des tables

--- Table Club

CREATE TABLE IF NOT EXISTS Club(idClub INTEGER PRIMARY KEY AUTOINCREMENT, nom VARCHAR);

--- Table Joueur

CREATE TABLE IF NOT EXISTS Joueur(idJoueur INTEGER PRIMARY KEY AUTOINCREMENT, pseudo VARCHAR, nom VARCHAR, prenom VARCHAR, UNIQUE(nom,prenom));

--- Table Equipe

CREATE TABLE IF NOT EXISTS Equipe(idEquipe INTEGER PRIMARY KEY AUTOINCREMENT, idClub INTEGER NOT NULL, idJoueur INTEGER NOT NULL, nomEquipe VARCHAR, CONSTRAINT fk_idClub_1 FOREIGN KEY (idClub) REFERENCES Club(idClub), CONSTRAINT fk_idJoueur_1 FOREIGN KEY (idJoueur) REFERENCES Joueur(idJoueur), UNIQUE(idClub,idJoueur));

--- Table Rencontre (match)

CREATE TABLE IF NOT EXISTS Rencontre(idRencontre INTEGER PRIMARY KEY AUTOINCREMENT, idEquipeA INTEGER NOT NULL, idEquipeB INTEGER NOT NULL, nbManchesGagnantes INTEGER DEFAULT 1, tempsMaxTir INTEGER DEFAULT 0, nbPaniers INTEGER DEFAULT 4, estFinie INTEGER DEFAULT 0, horodatage DATETIME NOT NULL, CONSTRAINT fk_idEquipe_A FOREIGN KEY (idEquipeA) REFERENCES Equipe(idEquipe), CONSTRAINT fk_idEquipe_B FOREIGN KEY (idEquipeB) REFERENCES Equipe(idEquipe));

--- Table Manche

CREATE TABLE IF NOT EXISTS Manche(idRencontre INTEGER NOT NULL, numeroManche INTEGER NOT NULL, nbPaniersEquipeA INTEGER DEFAULT 0, nbPaniersEquipeB INTEGER DEFAULT 0, vainqueur INTEGER DEFAULT 0, debut DATETIME NOT NULL, fin DATETIME, CONSTRAINT pk_manche PRIMARY KEY (idRencontre,numeroManche), CONSTRAINT fk_idRencontre_1 FOREIGN KEY (idRencontre) REFERENCES Rencontre(idRencontre), CONSTRAINT fk_vainqueur_1 FOREIGN KEY (vainqueur) REFERENCES Equipe(idEquipe));

--- Voir aussi :
--- ON DELETE CASCADE
