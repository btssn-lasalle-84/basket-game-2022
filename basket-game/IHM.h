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
 * @def TEST_IHM
 * @brief Pour le mode test (raccourcis clavier)
 */
#define TEST_IHM

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
    BaseDeDonnees* bdd; //!< Base de donnes
    Communication* communication;      //!< pour la communication bluetooth
    QVector<QStringList> listeEquipes; //!< La liste des équipes
    QVector<Equipe*>     equipes;      //!< Les deux équipes
    int                  idEquipeRougeSelectionnee; //!< L'id de l'équipe rouge
    int                  idEquipeJauneSelectionnee; //!< L'id de l'équipe jaune
    Seance*              seance;      //!< La séance entre deux équipes
    QTimer*              timerSeance; //!< Pour gérer les temps restants
    QTimer*              chronometrePartie;
    QElapsedTimer        tempsEcoulePartie;

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

#ifdef TEST_IHM
    void fixerRaccourcisClavier();
#endif

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
