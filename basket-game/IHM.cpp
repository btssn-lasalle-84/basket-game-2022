#include "IHM.h"
#include "ui_IHM.h"
#include "BaseDeDonnees.h"
#include "Communication.h"
#include "Equipe.h"
#include "Seance.h"
#include <QDebug>

/**
 * @file ihm.cpp
 *
 * @brief Définition de la classe IHM
 * @author Guillaume LAMBERT
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
IHM::IHM(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHM), bdd(nullptr), communication(nullptr),
    idEquipeRougeSelectionnee(-1), idEquipeJauneSelectionnee(-1),
    seance(nullptr), timerSeance(nullptr), chronometrePartie(nullptr)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

#ifdef TEST_IHM
    fixerRaccourcisClavier();
#endif

    initialiserRessources();
    initialiserEquipes();
    connecterSignalSlot();

    communication->rechercher();

    ui->boutonDemarrerPageConfiguration->setEnabled(false);
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
    communication->deconnecter();
    BaseDeDonnees::detruireInstance();
    for(int i = 0; i < equipes.size(); ++i)
        delete equipes[i];
    qDebug() << Q_FUNC_INFO;
}

void IHM::demarrerNouvellePartie()
{
    qDebug() << Q_FUNC_INFO;
    recupererEquipes();
    /**
     * @todo TODO Récupérer les temps dans la base de données
     */
    ui->tempsParTourEnSecondes->setValue(TEMPS_PAR_TOUR_DEFAUT);
    ui->tempsParPartieEnMinutes->setValue(TEMPS_PAR_PARTIE_DEFAUT);
    afficherPageConfiguration();
}

void IHM::selectionnerEquipeRouge(int numeroEquipe)
{
    Q_UNUSED(numeroEquipe)
    // Aucune équipe sélecionnée ?
    if(ui->listeEquipesRouges->currentIndex() <= 0)
    {
        equipes[CouleurEquipe::Rouge]->setNomEquipe("");
        equipes[CouleurEquipe::Rouge]->supprimerJoueurs();
        idEquipeRougeSelectionnee = -1;
        ui->lineEditNomEquipeRouge->setEnabled(true);
        ui->boutonDemarrerPageConfiguration->setEnabled(false);
        return;
    }
    qDebug() << Q_FUNC_INFO << ui->listeEquipesRouges->currentIndex() - 1
             << listeEquipes.at(ui->listeEquipesRouges->currentIndex() - 1);
    idEquipeRougeSelectionnee = ui->listeEquipesRouges->currentIndex() - 1;
    equipes[CouleurEquipe::Rouge]->setNomEquipe(
      listeEquipes.at(ui->listeEquipesRouges->currentIndex() - 1)
        .at(ChampsEquipe::NOM_EQUIPE));
    equipes[CouleurEquipe::Rouge]->setNbrPointEquipeRouge(0);
    equipes[CouleurEquipe::Rouge]->setNbrPointEquipeJaune(0);
    ajouterJoueurs(listeEquipes.at(ui->listeEquipesRouges->currentIndex() - 1)
                     .at(ChampsEquipe::ID_EQUIPE),
                   (int)Rouge);
    ui->lineEditNomEquipeRouge->setText("");
    ui->lineEditNomEquipeRouge->setEnabled(false);
    if(idEquipeRougeSelectionnee != -1 && idEquipeJauneSelectionnee != -1)
    {
        ui->boutonDemarrerPageConfiguration->setEnabled(true);
    }
}

void IHM::selectionnerEquipeJaune(int numeroEquipe)
{
    Q_UNUSED(numeroEquipe)
    // Aucune équipe sélecionnée ?
    if(ui->listeEquipesJaunes->currentIndex() <= 0)
    {
        equipes[CouleurEquipe::Jaune]->setNomEquipe("");
        equipes[CouleurEquipe::Jaune]->supprimerJoueurs();
        idEquipeJauneSelectionnee = -1;
        ui->lineEditNomEquipeJaune->setEnabled(true);
        ui->boutonDemarrerPageConfiguration->setEnabled(false);
        return;
    }
    qDebug() << Q_FUNC_INFO << ui->listeEquipesJaunes->currentIndex() - 1
             << listeEquipes.at(ui->listeEquipesJaunes->currentIndex() - 1);
    idEquipeJauneSelectionnee = ui->listeEquipesJaunes->currentIndex() - 1;
    equipes[CouleurEquipe::Jaune]->setNomEquipe(
      listeEquipes.at(ui->listeEquipesJaunes->currentIndex() - 1)
        .at(ChampsEquipe::NOM_EQUIPE));
    equipes[CouleurEquipe::Rouge]->setNbrPointEquipeRouge(0);
    equipes[CouleurEquipe::Rouge]->setNbrPointEquipeJaune(0);
    ajouterJoueurs(listeEquipes.at(ui->listeEquipesJaunes->currentIndex() - 1)
                     .at(ChampsEquipe::ID_EQUIPE),
                   (int)Jaune);
    ui->lineEditNomEquipeJaune->setText("");
    ui->lineEditNomEquipeJaune->setEnabled(false);
    if(idEquipeRougeSelectionnee != -1 && idEquipeJauneSelectionnee != -1)
    {
        ui->boutonDemarrerPageConfiguration->setEnabled(true);
    }
}

void IHM::saisirNouvelleEquipeRouge()
{
    qDebug() << Q_FUNC_INFO << ui->lineEditNomEquipeRouge->text();
    /**
     * @todo TODO insérer la nouvelle équipe dans la base de données et dans la
     * liste
     */
}

void IHM::saisirNouvelleEquipeJaune()
{
    qDebug() << Q_FUNC_INFO << ui->lineEditNomEquipeJaune->text();
    /**
     * @todo TODO insérer la nouvelle équipe dans la base de données et dans la
     * liste
     */
}

void IHM::saisirTempsParTourEnSecondes(int tempsParTourEnSecondes)
{
    qDebug() << Q_FUNC_INFO << tempsParTourEnSecondes;
    if(tempsParTourEnSecondes != 0)
    {
        /**
         * @todo  TODO modifier les paramètres dans la base de données
         */
        ui->tempsParTour->setChecked(true);
    }
    else
        ui->tempsParTour->setChecked(false);
}

void IHM::saisirTempsParPartieEnMinutes(int tempsParPartieEnMinutes)
{
    qDebug() << Q_FUNC_INFO << tempsParPartieEnMinutes;
    if(tempsParPartieEnMinutes != 0)
    {
        /**
         * @todo TODO modifier les paramètres dans la base de données
         */
        ui->tempsParPartie->setChecked(true);
    }
    else
        ui->tempsParPartie->setChecked(false);
}

void IHM::validerDemarragePartie()
{
    if(idEquipeRougeSelectionnee != -1 && idEquipeJauneSelectionnee != -1)
    {
        qDebug() << Q_FUNC_INFO << equipes[CouleurEquipe::Rouge]->getNomEquipe()
                 << equipes[CouleurEquipe::Jaune]->getNomEquipe();
        // séance déjà en cours ?!
        if(seance != nullptr)
        {
            delete seance;
            seance = nullptr;
        }
        // Il faut instancier une nouvelle séance
        seance = new Seance(equipes[CouleurEquipe::Jaune],
                            equipes[CouleurEquipe::Rouge],
                            this);
        ui->nomEquipeRouge_2->setText(
          equipes[CouleurEquipe::Rouge]->getNomEquipe());
        ui->nomEquipeJaune_2->setText(
          equipes[CouleurEquipe::Jaune]->getNomEquipe());
        ui->labelEquipeEnCours->setText(
          equipes[CouleurEquipe::Rouge]->getNomEquipe());
        qDebug() << Q_FUNC_INFO << "tempsParTour"
                 << ui->tempsParTour->checkState();
        qDebug() << Q_FUNC_INFO << "tempsParTourEnSecondes"
                 << ui->tempsParTourEnSecondes->value();
        if(ui->tempsParTour->checkState() == Qt::Checked)
        {
            ui->tempsTour->setText(
              QString::number(ui->tempsParTourEnSecondes->value()) +
              QString(" s"));
            seance->setDureeTempsTour(ui->tempsParTourEnSecondes->value());
        }
        else
        {
            ui->labelTempsTour->hide();
            ui->tempsTour->setText(QString(""));
            ui->tempsTour->hide();
            seance->setDureeTempsTour(0);
        }
        if(ui->tempsParPartie->checkState() == Qt::Checked)
        {
            ui->tempsPartie->setText(
              QString::number(ui->tempsParPartieEnMinutes->value()) +
              QString(" m"));
            seance->setDureeTempsPartie(ui->tempsParPartieEnMinutes->value());
        }
        else
        {
            ui->labelTempsTour->hide();
            ui->tempsTour->setText(QString(""));
            ui->tempsTour->hide();
            seance->setDureeTempsTour(0);
        }
        /**
         * @todo TODO Initialiser le reste de la page Partie
         */
        qDebug() << Q_FUNC_INFO << "tempsParPartieEnMinutes"
                 << ui->tempsParPartieEnMinutes->value();
        // ui->tempsPartie->setText("");

        // Il faut être connecté
        if(communication->estConnecte())
            ui->boutonGererPartiePagePartie->setEnabled(true);
        else
            ui->boutonGererPartiePagePartie->setEnabled(false);
        ui->messageVictoireEquipe->hide();
        afficherPagePartie();
    }
}

/**
 * @brief Démarre une partie de basket
 *
 */
void IHM::gererPartie()
{
    qDebug() << Q_FUNC_INFO;
    communication->envoyer("$basket;STT;\r");
    ui->boutonGererPartiePagePartie->setEnabled(false);
    initialiserPartie();
    demarrerChronometrePartie();
}

void IHM::ajouterPanier(QString numeroPanier, QString equipe)
{
    qDebug() << Q_FUNC_INFO << numeroPanier << equipe;
    ui->lcdNumberPointsEquipeRouge->display(seance->getNbPaniersEquipeRouge());
    ui->lcdNumberPointsEquipeJaune->display(seance->getNbPaniersEquipeJaune());
    if(numeroPanier != "0" && !seance->estFinie())
    {
        if(equipe == "J")
        {
            seance->marquerUnPointEquipeJaune();
            qDebug() << Q_FUNC_INFO << seance->getNbPaniersEquipeJaune();
            ui->lcdNumberPointsEquipeJaune->display(
              seance->getNbPaniersEquipeJaune());
            ui->labelEquipeEnCours->setText(seance->getNomEquipeRouge());
        }
        else if(equipe == "R")
        {
            seance->marquerUnPointEquipeRouge();
            qDebug() << Q_FUNC_INFO << seance->getNbPaniersEquipeRouge();
            ui->lcdNumberPointsEquipeRouge->display(
              seance->getNbPaniersEquipeRouge());
            ui->labelEquipeEnCours->setText(seance->getNomEquipeJaune());
        }
    }

    else if(numeroPanier == "0" && equipe == "R" && !seance->estFinie())
    {
        ui->labelEquipeEnCours->setText("Tir raté pour l'équipe " +
                                        seance->getNomEquipeRouge() + "!");
    }
    else if(numeroPanier == "0" && equipe == "J" && !seance->estFinie())
    {
        ui->labelEquipeEnCours->setText("Tir raté équipe " +
                                        seance->getNomEquipeJaune() + "!");
    }
    else if(seance->estFinie() &&
            seance->getNbPaniersEquipeJaune() == POINT_POUR_VICTOIRE)
    {
        ui->labelEquipeEnCours->setText("Bravo à l'équipe " +
                                        seance->getNomEquipeJaune() + " !");
    }
    else if(seance->estFinie() &&
            seance->getNbPaniersEquipeRouge() == POINT_POUR_VICTOIRE)
    {
        ui->labelEquipeEnCours->setText("Bravo à l'équipe " +
                                        seance->getNomEquipeRouge() + " !");
    }
}

void IHM::arreterPartie()
{
    qDebug() << Q_FUNC_INFO;
    if(communication != nullptr)
        communication->envoyer("$basket;STP;\r");
    ui->boutonGererPartiePagePartie->setEnabled(true);
    if(seance != nullptr)
        seance->setFinTemps(QTime::currentTime());
    if(timerSeance != nullptr && timerSeance->isActive())
        timerSeance->stop();
    arreterChronometrePartie();
}

void IHM::gererHorlogePartie()
{
    // qDebug() << Q_FUNC_INFO;
    if(seance != nullptr && !seance->estFinie())
    {
        QTime heureCourante = QTime::currentTime();
        int   tempsRestantTour =
          heureCourante.secsTo(seance->getDebutTempsTour());
        if(tempsRestantTour > 0)
        {
            ui->tempsTour->setText(QString::number(tempsRestantTour) +
                                   QString(" s"));
        }
        else
        {
            emit tempsTourExpiree();
        }

        int tempsRestantPartie = heureCourante.minute();
        if(tempsRestantPartie > 0)
        {
            ui->tempsPartie->setText(QString::number(tempsRestantPartie) +
                                     QString(" m"));
        }
    }
}

void IHM::demarrerChronometrePartie()
{
    if(chronometrePartie == nullptr)
    {
        chronometrePartie = new QTimer(this);
        connect(chronometrePartie,
                SIGNAL(timeout()),
                this,
                SLOT(gererChronometrePartie()));
    }
    if(chronometrePartie->isActive())
        arreterChronometrePartie();
    chronometrePartie->start(500);
    tempsEcoulePartie.start();
}

void IHM::arreterChronometrePartie()
{
    if(chronometrePartie != nullptr && chronometrePartie->isActive())
        chronometrePartie->stop();
}

void IHM::gererChronometrePartie()
{
    QTime tempsChronometre(0, 0);
    tempsChronometre = tempsChronometre.addMSecs(tempsEcoulePartie.elapsed());
    /**
     * @todo TODO Gérer le temps d'une partie et d'un tir
     */
    afficherChronometrePartie(tempsChronometre.toString("mm:ss"));
}

void IHM::afficherChronometrePartie(QString temps)
{
    ui->labelDuree->setText(temps);
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
    arreterPartie();
    afficherFenetre(IHM::PagePrincipale);
}

void IHM::afficherPageRegles()
{
    afficherFenetre(IHM::PageRegles);
}

void IHM::afficherPageConfiguration()
{
    if(seance != nullptr)
        arreterPartie();
    afficherFenetre(IHM::PageConfiguration);
}

void IHM::afficherPagePartie()
{
    afficherFenetre(IHM::PagePartie);
}

/**
 * @brief Méthode qui permet de quitter la fenêtre principale de
 * l'application
 *
 * @fn IHM::quitter
 */
void IHM::quitter()
{
    this->close();
    qDebug() << Q_FUNC_INFO;
}

void IHM::gererPeripherique(QString nom, QString adresseMAC)
{
    qDebug() << Q_FUNC_INFO << nom << adresseMAC;
    communication->connecter();
}

void IHM::afficherEtatConnexion()
{
    qDebug() << Q_FUNC_INFO;
}

void IHM::afficherEtatDeconnexion()
{
    qDebug() << Q_FUNC_INFO;
}

void IHM::terminerRecherche()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Initialise les ressources
 */
void IHM::initialiserRessources()
{
    bdd = BaseDeDonnees::getInstance();
    bdd->ouvrir(BDD);

    communication = new Communication(this);

    timerSeance = new QTimer(this);
}

/**
 * @brief Initialise les deux équipes
 */
void IHM::initialiserEquipes()
{
    // crée les deux équipes
    equipes.push_back(new Equipe);
    equipes.push_back(new Equipe);
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
            SLOT(validerDemarragePartie()));
    connect(ui->listeEquipesRouges,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(selectionnerEquipeRouge(int)));
    connect(ui->listeEquipesJaunes,
            SIGNAL(currentIndexChanged(int)),
            this,
            SLOT(selectionnerEquipeJaune(int)));
    connect(ui->lineEditNomEquipeRouge,
            SIGNAL(editingFinished()),
            this,
            SLOT(saisirNouvelleEquipeRouge()));
    connect(ui->lineEditNomEquipeJaune,
            SIGNAL(editingFinished()),
            this,
            SLOT(saisirNouvelleEquipeJaune()));
    connect(ui->tempsParTourEnSecondes,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(saisirTempsParTourEnSecondes(int)));
    connect(ui->tempsParPartieEnMinutes,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(saisirTempsParPartieEnMinutes(int)));
    // PagePartie
    connect(ui->boutonRetourPagePartie,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherPageConfiguration()));
    connect(ui->boutonRetourPrincipalePagePartie,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherPagePrincipale()));
    connect(ui->boutonGererPartiePagePartie,
            SIGNAL(clicked(bool)),
            this,
            SLOT(gererPartie()));
    connect(timerSeance, SIGNAL(timeout()), this, SLOT(gererHorlogePartie()));
    // Ajout d'un point pour une équipe
    connect(communication,
            SIGNAL(nouveauPanier(QString, QString)),
            this,
            SLOT(ajouterPanier(QString, QString)));
    // Communication
    connect(communication,
            SIGNAL(peripheriqueDetecte(QString, QString)),
            this,
            SLOT(gererPeripherique(QString, QString)));
    connect(communication,
            SIGNAL(peripheriqueConnecte()),
            this,
            SLOT(afficherEtatConnexion()));
    connect(communication,
            SIGNAL(peripheriqueDeconnecte()),
            this,
            SLOT(afficherEtatDeconnexion()));
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

    listeEquipes.clear();
    bool retour = bdd->recuperer(requete, listeEquipes);
    qDebug() << Q_FUNC_INFO << listeEquipes;
    if(retour)
    {
        ui->listeEquipesRouges->clear();
        ui->listeEquipesJaunes->clear();
        ui->listeEquipesRouges->addItem("");
        ui->listeEquipesJaunes->addItem("");
        for(int i = 0; i < listeEquipes.size(); ++i)
            afficherListeEquipe(listeEquipes.at(i));
    }
}

void IHM::ajouterJoueurs(QString idEquipe, int couleurEquipe)
{
    if(idEquipe.isEmpty())
        return;
    qDebug() << Q_FUNC_INFO << idEquipe;
    QString requete = "SELECT Equipe.idEquipe, Equipe.idClub, Equipe.idJoueur, "
                      "Equipe.nomEquipe, Club.nom AS nomClub, Joueur.pseudo, "
                      "Joueur.nom, Joueur.prenom FROM Equipe "
                      "INNER JOIN Club ON Equipe.idClub=Club.idClub "
                      "INNER JOIN Joueur ON Equipe.idJoueur=Joueur.idJoueur "
                      "WHERE Equipe.idEquipe = '" +
                      idEquipe + "';";

    QVector<QStringList> listeJoueurs;
    bool                 retour = bdd->recuperer(requete, listeJoueurs);
    qDebug() << Q_FUNC_INFO << listeJoueurs;
    if(retour)
    {
        equipes[couleurEquipe]->supprimerJoueurs();
        for(int i = 0; i < listeJoueurs.size(); ++i)
            equipes[couleurEquipe]->ajouterJoueur(listeJoueurs.at(i).at(0));
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

void IHM::initialiserPartie()
{
    seance->setNbPaniersEquipeJaune(0);
    seance->setNbPaniersEquipeRouge(0);
    seance->setDebutTemps(QTime::currentTime());
    seance->setDebutTempsTour(QTime::currentTime());
    timerSeance->start(500);
}
