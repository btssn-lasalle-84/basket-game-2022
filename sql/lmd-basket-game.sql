--- LMD (langage de manipulation de données)

--- Contenu des tables (tests)

--- Table Club

INSERT INTO Club (idClub, nom) VALUES (NULL,'');
INSERT INTO Club (idClub, nom) VALUES (NULL,'Bulls');
INSERT INTO Club (idClub, nom) VALUES (NULL,'Lakers');
INSERT INTO Club (idClub, nom) VALUES (NULL,'Celtics');
INSERT INTO Club (idClub, nom) VALUES (NULL,'Bucks');
INSERT INTO Club (idClub, nom) VALUES (NULL,'Sixers');
INSERT INTO Club (idClub, nom) VALUES (NULL,'Spurs');

--- Table Joueur

INSERT INTO Joueur(idJoueur, pseudo, nom, prenom) VALUES (null,'Air Jordan','JORDAN','Mickael');
INSERT INTO Joueur(idJoueur, pseudo, nom, prenom) VALUES (null,'King James','LEBRON','James');
INSERT INTO Joueur(idJoueur, pseudo, nom, prenom) VALUES (null,'The Good Lord','RUSSEL','Bill');
INSERT INTO Joueur(idJoueur, pseudo, nom, prenom) VALUES (null,'Magic','JOHNSON','Earvin');
INSERT INTO Joueur(idJoueur, pseudo, nom, prenom) VALUES (null,'Black Mamba','BRYANT','Kobe');
INSERT INTO Joueur(idJoueur, pseudo, nom, prenom) VALUES (null,'TP','PARKER','Tony');

INSERT INTO Joueur(idJoueur, pseudo, nom, prenom) VALUES (null,'','LAMBERT','Guillaume');
INSERT INTO Joueur(idJoueur, pseudo, nom, prenom) VALUES (null,'','LADRIERE','Enzo');

--- Table Equipe

INSERT INTO Equipe(idClub, idJoueur, nomEquipe) VALUES (2,1,'');
INSERT INTO Equipe(idClub, idJoueur, nomEquipe) VALUES (3,2,'');
INSERT INTO Equipe(idClub, idJoueur, nomEquipe) VALUES (4,3,'');
INSERT INTO Equipe(idClub, idJoueur, nomEquipe) VALUES (3,4,'');
INSERT INTO Equipe(idClub, idJoueur, nomEquipe) VALUES (3,5,'');
INSERT INTO Equipe(idClub, idJoueur, nomEquipe) VALUES (7,6,'');

INSERT INTO Equipe(idClub, idJoueur, nomEquipe) VALUES (1,7,'');
INSERT INTO Equipe(idClub, idJoueur, nomEquipe) VALUES (1,8,'');

--- Table Rencontre

INSERT INTO Rencontre(idRencontre, idEquipeA, idEquipeB, nbManchesGagnantes, estFinie, horodatage) VALUES (NULL,7,8,2,0,'2022-01-29 08:00:00');

--- Table Manche

INSERT INTO Manche(idRencontre, numeroManche, nbPaniersEquipeA, nbPaniersEquipeB, vainqueur, debut) VALUES (1,1,4,3,7,'2022-01-29 08:15:00');
INSERT INTO Manche(idRencontre, numeroManche, nbPaniersEquipeA, nbPaniersEquipeB, vainqueur, debut) VALUES (1,2,1,4,8,'2022-01-29 08:20:00');
INSERT INTO Manche(idRencontre, numeroManche, nbPaniersEquipeA, nbPaniersEquipeB, vainqueur, debut) VALUES (1,3,4,0,7,'2022-01-29 08:45:00');
