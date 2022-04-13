#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHM
 * @author
 * @version 1.0
 *
 */

#include <QtWidgets>

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

// QT_BEGIN_NAMESPACE
namespace Ui
{
class IHM;
}
// QT_END_NAMESPACE

class BaseDeDonnees;
class Equipe;

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
    QVector<QStringList> listeEquipes;              //!< La liste des équipes
    QVector<Equipe*>     equipes;                   //!< Les deux équipes
    int                  idEquipeRougeSelectionnee; //!< L'id de l'équipe rouge
    int                  idEquipeJauneSelectionnee; //!< L'id de l'équipe jaune

    void connecterSignalSlot();
    void recupererEquipes();
    void ajouterJoueurs(QString idEquipe, int couleurEquipe);
    void afficherListeEquipe(QStringList equipe);

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
     * @enum ChampsTableSalle
     * @brief Définit les différents champs de la table Salle
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
    void afficherFenetre(IHM::Fenetre fenetre);
    void afficherFenetrePrecedente();
    void afficherFenetreSuivante();
    void afficherPagePrincipale();
    void afficherPageRegles();
    void afficherPageConfiguration();
    void afficherPagePartie();
    void quitter();
};

#endif // IHM_H
