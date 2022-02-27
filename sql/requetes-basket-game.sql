--- Exemples et exercices d'accompagnement : déterminer les requêtes SQL

--- Liste des joueurs



--- Nombre de joueurs



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



--- Nombre de clubs



--- Liste des équipes



--- Nombre d'équipes



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



--- Liste des joueurs pour un club



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



--- Liste des manches



--- Liste de toutes les manches d'une rencontre



--- Liste de toutes parties pour une rencontre avec les noms des joueurs


---- Commencer une manche



---- Finir une manche et enregistrer le vainqueur


