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
 * @def PLEIN_ECRAN
 * @brief Pour le mode kiosque de la télévision
 */
#define PLEIN_ECRAN

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

  private:
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

    void initialiserRessources();
    void initialiserEquipes();
    void connecterSignalSlot();
    void recupererEquipes();
    void ajouterJoueurs(QString idEquipe, int couleurEquipe);
    void afficherListeEquipe(QStringList equipe);
    void initialiserPartie();

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
