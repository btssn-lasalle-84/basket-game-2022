--- Exemples et exercices d'accompagnement : déterminer les requêtes SQL

--- Liste des joueurs

SELECT * FROM Joueur;

| idJoueur | pseudo        | nom      | prenom    |
| -------- | ------------- | -------- | --------- |
| 1        | Air Jordan    | JORDAN   | Mickael   |
| 2        | King James    | LEBRON   | James     |
| 3        | The Good Lord | RUSSEL   | Bill      |
| 4        | Magic         | JOHNSON  | Earvin    |
| 5        | Black Mamba   | BRYANT   | Kobe      |
| 6        | TP            | PARKER   | Tony      |
| 7        |               | LAMBERT  | Guillaume |
| 8        |               | LADRIERE | Enzo      |

--- Nombre de joueurs

SELECT COUNT(*) AS NbJoueurs FROM Joueur;

| NbJoueurs |
| --------- |
| 8         |

--- Liste des noms complets des joueurs

SELECT nom || ' ' || prenom AS NomJoueur FROM Joueur ORDER BY NomJoueur;

|     NomJoueur     |
| ----------------- |
| BRYANT Kobe       |
| JOHNSON Earvin    |
| JORDAN Mickael    |
| LADRIERE Enzo     |
| LAMBERT Guillaume |
| LEBRON James      |
| PARKER Tony       |
| RUSSEL Bill       |

--- Liste des clubs

SELECT * FROM Club;

--- Nombre de clubs

SELECT COUNT(*) AS NbClubs FROM Club;


--- Liste des équipes

SELECT * FROM Equipe;

--- Nombre d'équipes

SELECT COUNT(*) AS NbEquipes FROM Equipe;

--- Liste des joueurs par equipe

SELECT Equipe.idEquipe, Equipe.idClub, Equipe.idJoueur, Equipe.nomEquipe, Club.nom AS nomClub, Joueur.pseudo, Joueur.nom, Joueur.prenom FROM Equipe 
INNER JOIN Club ON Equipe.idClub=Club.idClub 
INNER JOIN Joueur ON Equipe.idJoueur=Joueur.idJoueur;

| idEquipe | idClub | idJoueur | nomEquipe | nomClub | pseudo        | nom      | prenom    |
| -------- | ------ | -------- | --------- | ------- | ------------- | -------- | --------- |
| 1        | 2      | 1        |           | Bulls   | Air Jordan    | JORDAN   | Mickael   |
| 2        | 3      | 2        |           | Lakers  | King James    | LEBRON   | James     |
| 3        | 4      | 3        |           | Celtics | The Good Lord | RUSSEL   | Bill      |
| 4        | 3      | 4        |           | Lakers  | Magic         | JOHNSON  | Earvin    |
| 5        | 3      | 5        |           | Lakers  | Black Mamba   | BRYANT   | Kobe      |
| 6        | 7      | 6        |           | Spurs   | TP            | PARKER   | Tony      |
| 7        | 1      | 7        |           |         |               | LAMBERT  | Guillaume |
| 8        | 1      | 8        |           |         |               | LADRIERE | Enzo      |

--- Liste des joueurs pour une equipe

SELECT Equipe.idEquipe, Equipe.idClub, Equipe.idJoueur, Equipe.nomEquipe, Club.nom AS nomClub, Joueur.pseudo, Joueur.nom, Joueur.prenom FROM Equipe 
INNER JOIN Club ON Equipe.idClub=Club.idClub 
INNER JOIN Joueur ON Equipe.idJoueur=Joueur.idJoueur 
WHERE Equipe.idEquipe = '1';

--- Liste des joueurs pour un club

SELECT Club.idClub, Club.nom AS nomClub, Joueur.pseudo, Joueur.nom, Joueur.prenom FROM Equipe 
INNER JOIN Club ON Equipe.idClub=Club.idClub 
INNER JOIN Joueur ON Equipe.idJoueur=Joueur.idJoueur 
WHERE Club.idClub = '1';

--- Liste des rencontres

SELECT * FROM Rencontre;

SELECT * FROM Rencontre 
INNER JOIN Equipe a ON (a.idEquipe = Rencontre.idEquipeA) 
INNER JOIN Equipe b ON (b.idEquipe = Rencontre.idEquipeB);

| idRencontre | idEquipeA | idEquipeB | nbManchesGagnantes | tempsMaxTir | nbPaniers | estFinie | horodatage          | idEquipe | idClub | idJoueur | nomEquipe | idEquipe | idClub | idJoueur | nomEquipe |
| ----------- | --------- | --------- | ------------------ | ----------- | --------- | -------- | ------------------- | -------- | ------ | -------- | --------- | -------- | ------ | -------- | --------- |
| 1           | 7         | 8         | 2                  | 0           | 4         | 0        | 2022-01-29 08:00:00 | 7        | 1      | 7        |           | 8        | 1      | 8        |           |

--- Détails des rencontres

SELECT Rencontre.idRencontre, Rencontre.nbManchesGagnantes, Rencontre.tempsMaxTir, Rencontre.nbPaniers, Rencontre.horodatage, Rencontre.estFinie, Rencontre.idEquipeA, equipeA.nomEquipe, clubA.idClub, clubA.nom AS nomClubA, joueurA.pseudo, joueurA.nom, joueurA.prenom, Rencontre.idEquipeB, equipeB.nomEquipe, clubB.idClub, clubB.nom AS nomClubB, joueurB.pseudo, joueurB.nom, joueurB.prenom FROM Rencontre 
INNER JOIN Equipe equipeA ON (equipeA.idEquipe = Rencontre.idEquipeA) 
INNER JOIN Equipe equipeB ON (equipeB.idEquipe = Rencontre.idEquipeB)
INNER JOIN Club clubA ON (equipeA.idClub = clubA.idClub)
INNER JOIN Club clubB ON (equipeB.idClub = clubB.idClub)
INNER JOIN Joueur joueurA ON (equipeA.idJoueur = joueurA.idJoueur)
INNER JOIN Joueur joueurB ON (equipeB.idJoueur = joueurB.idJoueur) ;

| idRencontre | nbManchesGagnantes | tempsMaxTir | nbPaniers | horodatage          | estFinie | idEquipeA | nomEquipe | idClub | nomClubA | pseudo | nom     | prenom    | idEquipeB | nomEquipe | idClub | nomClubB | pseudo | nom      | prenom |
| ----------- | ------------------ | ----------- | --------- | ------------------- | -------- | --------- | --------- | ------ | -------- | ------ | ------- | --------- | --------- | --------- | ------ | -------- | ------ | -------- | ------ |
| 1           | 2                  | 0           | 4         | 2022-01-29 08:00:00 | 0        | 7         |           | 1      |          |        | LAMBERT | Guillaume | 8         |           | 1      |          |        | LADRIERE | Enzo   |

--- Terminer une rencontre

--- UPDATE Rencontre SET estFinie=1 WHERE idRencontre='1';

--- Liste des manches

SELECT * FROM Manche;

--- Liste de toutes les manches d'une rencontre

SELECT * FROM Manche 
INNER JOIN Rencontre ON Manche.idRencontre = Rencontre.idRencontre 
INNER JOIN Equipe equipeA ON (equipeA.idEquipe = Rencontre.idEquipeA) 
INNER JOIN Equipe equipeB ON (equipeB.idEquipe = Rencontre.idEquipeB) 
WHERE Rencontre.idRencontre = '1';

--- Liste de toutes parties pour une rencontre avec les noms des joueurs

SELECT * FROM Manche 
INNER JOIN Rencontre ON Manche.idRencontre = Rencontre.idRencontre 
INNER JOIN Equipe equipeA ON (equipeA.idEquipe = Rencontre.idEquipeA) 
INNER JOIN Equipe equipeB ON (equipeB.idEquipe = Rencontre.idEquipeB)
INNER JOIN Club clubA ON (equipeA.idClub = clubA.idClub)
INNER JOIN Club clubB ON (equipeB.idClub = clubB.idClub)
INNER JOIN Joueur joueurA ON (equipeA.idJoueur = joueurA.idJoueur)
INNER JOIN Joueur joueurB ON (equipeB.idJoueur = joueurB.idJoueur)
WHERE Rencontre.idRencontre = '1';

| idRencontre | numeroManche | nbPaniersEquipeA | nbPaniersEquipeB | vainqueur | debut               | fin  | idRencontre | idEquipeA | idEquipeB | nbManchesGagnantes | tempsMaxTir | nbPaniers | estFinie | horodatage          | idEquipe | idClub | idJoueur | nomEquipe | idEquipe | idClub | idJoueur | nomEquipe | idClub | nom | idClub | nom | idJoueur | pseudo | nom     | prenom    | idJoueur | pseudo | nom      | prenom |
| ----------- | ------------ | ---------------- | ---------------- | --------- | ------------------- | ---- | ----------- | --------- | --------- | ------------------ | ----------- | --------- | -------- | ------------------- | -------- | ------ | -------- | --------- | -------- | ------ | -------- | --------- | ------ | --- | ------ | --- | -------- | ------ | ------- | --------- | -------- | ------ | -------- | ------ |
| 1           | 1            | 4                | 3                | 7         | 2022-01-29 08:15:00 | NULL | 1           | 7         | 8         | 2                  | 0           | 4         | 0        | 2022-01-29 08:00:00 | 7        | 1      | 7        |           | 8        | 1      | 8        |           | 1      |     | 1      |     | 7        |        | LAMBERT | Guillaume | 8        |        | LADRIERE | Enzo   |
| 1           | 2            | 1                | 4                | 8         | 2022-01-29 08:20:00 | NULL | 1           | 7         | 8         | 2                  | 0           | 4         | 0        | 2022-01-29 08:00:00 | 7        | 1      | 7        |           | 8        | 1      | 8        |           | 1      |     | 1      |     | 7        |        | LAMBERT | Guillaume | 8        |        | LADRIERE | Enzo   |
| 1           | 3            | 4                | 0                | 7         | 2022-01-29 08:45:00 | NULL | 1           | 7         | 8         | 2                  | 0           | 4         | 0        | 2022-01-29 08:00:00 | 7        | 1      | 7        |           | 8        | 1      | 8        |           | 1      |     | 1      |     | 7        |        | LAMBERT | Guillaume | 8        |        | LADRIERE | Enzo   |

---- Commencer une manche

INSERT INTO Manche(idRencontre,numeroManche,nbPaniersEquipeA,nbPaniersEquipeB, debut) VALUES (1,1,0,0,DATETIME('now'));

---- Finir une manche et enregistrer le vainqueur

UPDATE Manche SET fin=DATETIME('now'), nbPaniersEquipeA='4', nbPaniersEquipeB='1', vainqueur='7' WHERE idRencontre='1' AND numeroManche='3';

