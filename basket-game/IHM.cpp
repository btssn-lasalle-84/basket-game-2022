#include "IHM.h"
#include "ui_IHM.h"
#include "BaseDeDonnees.h"
#include <QDebug>

/**
 * @file ihm.cpp
 *
 * @brief Définition de la classe IHM
 * @author
 * @version 1.0
 *
 */

/**
 * @brief Constructeur de la classe IHM
 *
 * @fn IHM::IHM
 * @param parent L'adresse de l'objet parent, si nullptr IHM sera la
 * fenêtre principale de l'application
 */
IHM::IHM(QWidget* parent) : QMainWindow(parent), ui(new Ui::IHM)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

#ifdef TEST_IHM
    fixerRaccourcisClavier();
#endif

    bdd = BaseDeDonnees::getInstance();
    bdd->ouvrir("basket-game.sqlite");

    connecterSignalSlot();

    afficherFenetre(IHM::PagePrincipale);

#ifdef PLEIN_ECRAN
    showFullScreen();
// showMaximized();
#endif
}

/**
 * @brief Destructeur de la classe IHM
 *
 * @fn IHM::~IHM
 * @details Libère les ressources de l'application
 */
IHM::~IHM()
{
    delete ui;
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

void IHM::demarrerNouvellePartie()
{
    qDebug() << Q_FUNC_INFO;
    recupererEquipes();
    afficherPageConfiguration();
}

/**
 * @brief Méthode qui permet d'afficher un numéro de fenêtre de la pile
 * QStackedWidget
 *
 * @fn IHM::afficherFenetre
 * @param fenetre le numéro de fenêtre à afficher
 */
void IHM::afficherFenetre(IHM::Fenetre fenetre)
{
    qDebug() << Q_FUNC_INFO << "fenetre" << fenetre;
    ui->fenetres->setCurrentIndex(fenetre);
}

/**
 * @brief Méthode qui permet d'afficher la fenêtre suivante dans la pile
 * QStackedWidget
 *
 * @fn IHM::afficherFenetreSuivante
 */
void IHM::afficherFenetreSuivante()
{
    int fenetreCourante = IHM::Fenetre(ui->fenetres->currentIndex());
    int fenetreSuivante = (fenetreCourante + 1) % int(IHM::NbFenetres);
    afficherFenetre(IHM::Fenetre(fenetreSuivante));
}

/**
 * @brief Méthode qui permet d'afficher la fenêtre précédente dans la pile
 * QStackedWidget
 *
 * @fn IHM::afficherFenetrePrecedente
 */
void IHM::afficherFenetrePrecedente()
{
    int fenetreCourante   = ui->fenetres->currentIndex();
    int fenetrePrecedente = (fenetreCourante - 1) % int(IHM::NbFenetres);
    if(fenetrePrecedente == -1)
        fenetrePrecedente = int(IHM::NbFenetres) - 1;
    afficherFenetre(IHM::Fenetre(fenetrePrecedente));
}

void IHM::afficherPagePrincipale()
{
    afficherFenetre(IHM::PagePrincipale);
}

void IHM::afficherPageRegles()
{
    afficherFenetre(IHM::PageRegles);
}

void IHM::afficherPageConfiguration()
{
    afficherFenetre(IHM::PageConfiguration);
}

void IHM::afficherPagePartie()
{
    afficherFenetre(IHM::PagePartie);
}

/**
 * @brief Méthode qui permet de quitter la fenêtre principale de l'application
 *
 * @fn IHM::quitter
 */
void IHM::quitter()
{
    this->close();
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Assure la connexion des signaux aux slots
 *
 * @fn IHM::connecterSignalSlot
 */
void IHM::connecterSignalSlot()
{
    // PagePrincipale
    connect(ui->boutonNouvellePartiePagePrincipale,
            SIGNAL(clicked(bool)),
            this,
            SLOT(demarrerNouvellePartie()));
    connect(ui->boutonReglesPagePrincipale,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherPageRegles()));
    connect(ui->boutonQuitterPagePrincipale,
            SIGNAL(clicked(bool)),
            this,
            SLOT(quitter()));
    // PageRegles
    connect(ui->boutonRetourPageRegles,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherPagePrincipale()));
    // PageConfiguration
    connect(ui->boutonRetourPageConfiguration,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherPagePrincipale()));
    connect(ui->boutonDemarrerPageConfiguration,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherPagePartie()));
    // PagePartie
    connect(ui->boutonRetourPagePartie,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherPageConfiguration()));
    connect(ui->boutonRetourPrincipalePagePartie,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherPagePrincipale()));
}

#ifdef TEST_IHM
/**
 * @brief Méthode qui initialise les raccourcis clavier
 *
 * @fn IHMArbitre::fixerRaccourcisClavier
 */
void IHM::fixerRaccourcisClavier()
{
    // Ctrl-Q pour quitter
    QAction* quitter = new QAction(this);
    quitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    addAction(quitter);
    connect(quitter, SIGNAL(triggered()), this, SLOT(quitter()));

    // Flèche droite pour écran suivant
    QAction* actionAllerDroite = new QAction(this);
    actionAllerDroite->setShortcut(QKeySequence(Qt::Key_Right));
    addAction(actionAllerDroite);
    connect(actionAllerDroite,
            SIGNAL(triggered()),
            this,
            SLOT(afficherFenetreSuivante()));

    // Flèche gauche pour écran précédent
    QAction* actionAllerGauche = new QAction(this);
    actionAllerGauche->setShortcut(QKeySequence(Qt::Key_Left));
    addAction(actionAllerGauche);
    connect(actionAllerGauche,
            SIGNAL(triggered()),
            this,
            SLOT(afficherFenetrePrecedente()));
}
#endif

void IHM::recupererEquipes()
{
    QString requete =
      "SELECT Equipe.idEquipe, Equipe.idClub, Equipe.idJoueur, "
      "Equipe.nomEquipe, Club.nom AS nomClub, Joueur.pseudo, Joueur.nom, "
      "Joueur.prenom FROM Equipe "
      "INNER JOIN Club ON Equipe.idClub=Club.idClub "
      "INNER JOIN Joueur ON Equipe.idJoueur=Joueur.idJoueur;";

    bool retour = bdd->recuperer(requete, equipes);
    qDebug() << Q_FUNC_INFO << equipes;
    if(retour)
    {
        ui->listeEquipesRouges->clear();
        ui->listeEquipesJaunes->clear();
        for(int i = 0; i < equipes.size(); ++i)
            afficherListeEquipe(equipes.at(i));
    }
}

void IHM::afficherListeEquipe(QStringList equipe)
{
    if(!equipe.at(ChampsEquipe::NOM_EQUIPE).isEmpty())
    {
        ui->listeEquipesRouges->addItem(equipe.at(ChampsEquipe::NOM_EQUIPE));
        ui->listeEquipesJaunes->addItem(equipe.at(ChampsEquipe::NOM_EQUIPE));
    }
    else if(!equipe.at(ChampsEquipe::PSEUDO_JOUEUR).isEmpty())
    {
        ui->listeEquipesRouges->addItem(equipe.at(ChampsEquipe::PSEUDO_JOUEUR));
        ui->listeEquipesJaunes->addItem(equipe.at(ChampsEquipe::PSEUDO_JOUEUR));
    }
}
