#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHM
 * @author Guillaume LAMBERT
 * @version 1.0
 *
 */

#include <QtWidgets>

/**
 * @def BDD
 * @brief Définit le nom de la base de données
 */
#define BDD "basket-game.sqlite"

/**
 * @def DEPLACEMENT_LIGNE
 * @brief Définit la constante de déplacement en ligne sur l'axe X
 */
#define DEPLACEMENT_LIGNE 42

/**
 * @def DEPLACEMENT_COLONNE
 * @brief Définit la constante de déplacement en colonne sur l'axe Y
 */
#define DEPLACEMENT_COLONNE 321

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode kiosque de la télévision
 */
#define PLEIN_ECRAN

/**
 * @def NB_PANIERS
 * @brief Définit la constante du nombre de panier
 */
#define NB_PANIERS 7 // colonnes

/**
 * @def NB_LIGNES
 * @brief Définit la constante du nombre de ligne
 */

#define NB_LIGNES 6 // rangées

#define NB_PIONS_ALIGNES 4

namespace Ui
{
class IHM;
}

class BaseDeDonnees;
class Communication;
class Equipe;
class Seance;

/**
 * @class IHM
 * @brief Déclaration de la classe IHM
 * @details Cette classe s'occupe de l'affichage sur l'écran de télévision
 */
class IHM : public QMainWindow
{
    Q_OBJECT

  public:
    IHM(QWidget* parent = nullptr);
    ~IHM();

    /*void ajouterJetonColonne1();

    void ajouterJetonColonne0(QImage   pionRouge,
                              QString  numeroPanier,
                              QString  equipe,
                              QPainter p);*/

  private:
    /**
     * @enum Fenetre
     * @brief Définit les différents fenêtres de l'IHM
     *
     */
    enum Fenetre
    {
        PagePrincipale = 0,
        PageRegles,
        PageConfiguration,
        PagePartie,
        PageFinale,
        NbFenetres
    };

    /**
     * @enum CouleurEquipe
     * @brief Définit les couleurs des deux équipes
     *
     */
    enum CouleurEquipe
    {
        Rouge = 0,
        Jaune,
        NbEquipes
    };

    /**
     * @enum CouleurJeton
     * @brief Définit les différentes couleurs d'un jeton
     */
    enum CouleurJeton
    {
        ROUGE = -1,
        AUCUN = 0,
        JAUNE = 1,
        NbJeton /* = 2 */
    };

    /**
     * @enum ChampsEquipe
     * @brief Définit les différents champs d'e la table Salle'une équipe
     */
    enum ChampsEquipe
    {
        ID_EQUIPE,     //!< l'id de l'équipe
        ID_CLUB,       //!< l'id du club
        ID_JOUEUR,     //!< l'id du joueur
        NOM_EQUIPE,    //!< le nom de l'équipe
        NOM_CLUB,      //!< le nom du club
        PSEUDO_JOUEUR, //!< le pseudo du joueur
        NOM_JOUEUR,    //!< le nom du joueur
        PRENOM_JOUEUR, //!< le prénom du joueur
        NbChampsEquipe
    };

    Ui::IHM*       ui;  //!< la fenêtre graphique associée à cette classe
    BaseDeDonnees* bdd; //!< base de donnes
    Communication* communication;      //!< pour la communication bluetooth
    QVector<QStringList> listeEquipes; //!< la liste des équipes
    QVector<Equipe*>     equipes;      //!< les deux équipes
    int                  idEquipeRougeSelectionnee; //!< l'id de l'équipe rouge
    int                  idEquipeJauneSelectionnee; //!< l'id de l'équipe jaune
    Seance*              seance;      //!< la séance entre deux équipes
    QTimer*              timerSeance; //!< pour gérer les temps restants
    QTimer*       chronometrePartie;  //!< pour le chronmétrage d'une partie
    QElapsedTimer tempsEcoulePartie;  //!< pour gérer le temps écoulé
    QVector<QVector<CouleurJeton> > plateau; //! QVector<QVector<int> > plateau
    bool                            etatPartie; //! true si un gagnant
    int                             nbPaniers;  //! nombre de paniers

    void         initialiserRessources();
    void         initialiserEquipes();
    void         connecterSignalSlot();
    void         recupererEquipes();
    void         ajouterJoueurs(QString idEquipe, int couleurEquipe);
    void         afficherListeEquipe(QStringList equipe);
    void         initialiserPartie();
    void         afficherPlateau();
    void         initialiserPlateau();
    CouleurJeton verifierLigne(int ligne);
    CouleurJeton verifierColonne(int colonne);
    CouleurJeton verifierDiagonales();
    bool         aGagne(CouleurJeton couleurEquipe);
    bool         estRempli();

  public slots:
    void demarrerNouvellePartie();
    void selectionnerEquipeRouge(int numeroEquipe);
    void selectionnerEquipeJaune(int numeroEquipe);
    void saisirNouvelleEquipeRouge();
    void saisirNouvelleEquipeJaune();
    void saisirTempsParTourEnSecondes(int tempsParTourEnSecondes);
    void saisirTempsParPartieEnMinutes(int tempsParPartieEnMinutes);
    void validerDemarragePartie();
    void gererPartie();
    void ajouterPanier(QString numeroPanier, QString equipe);
    int  jouerUnJeton(QString numeroPanier, QString equipe);
    void arreterPartie();
    void gererHorlogePartie();
    void demarrerChronometrePartie();
    void arreterChronometrePartie();
    void gererChronometrePartie();
    void afficherChronometrePartie(QString temps);
    void afficherFenetre(IHM::Fenetre fenetre);
    void afficherFenetrePrecedente();
    void afficherFenetreSuivante();
    void afficherPagePrincipale();
    void afficherPageRegles();
    void afficherPageConfiguration();
    void afficherPagePartie();
    void quitter();
    void gererPeripherique(QString, QString);
    void afficherEtatConnexion();
    void afficherEtatDeconnexion();
    void terminerRecherche();

  signals:
    void tempsTourExpiree();
};

#endif // IHM_H
