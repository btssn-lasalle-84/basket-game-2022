#include "IHM.h"
#include "ui_IHM.h"
#include "BaseDeDonnees.h"
#include "Communication.h"
#include "Equipe.h"
#include "Seance.h"
#include <QDebug>
#include <QPainter>

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
    seance(nullptr), timerSeance(nullptr), chronometrePartie(nullptr),
    plateau(NB_PANIERS), etatPartie(false)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

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

/**
 * @brief Pépare une nouvelle partie
 */
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

/**
 * @brief Sélectionne une équipe pour les rouges
 */
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

    // prêt ?
    if(idEquipeRougeSelectionnee != -1 && idEquipeJauneSelectionnee != -1)
    {
        ui->boutonDemarrerPageConfiguration->setEnabled(true);
    }
}

/**
 * @brief Sélectionne une équipe pour les jaunes
 */
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

    // prêt
    if(idEquipeRougeSelectionnee != -1 && idEquipeJauneSelectionnee != -1)
    {
        ui->boutonDemarrerPageConfiguration->setEnabled(true);
    }
}

/**
 * @brief Ajoute une nouvelle équipe Rouge
 */
void IHM::saisirNouvelleEquipeRouge()
{
    qDebug() << Q_FUNC_INFO << ui->lineEditNomEquipeRouge->text();
    /**
     * @todo TODO insérer la nouvelle équipe dans la base de données et dans la
     * liste
     */
}

/**
 * @brief Ajoute une nouvelle équipe Jaune
 */
void IHM::saisirNouvelleEquipeJaune()
{
    qDebug() << Q_FUNC_INFO << ui->lineEditNomEquipeJaune->text();
    /**
     * @todo TODO insérer la nouvelle équipe dans la base de données et dans la
     * liste
     */
}

/**
 * @brief Assure la saisie du temps par tour
 */
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

/**
 * @brief Assure la saisie du temps d'une partie
 */
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

/**
 * @brief Valide une partie à démarrer
 */
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
        ui->labelVisualisationPuissance4->show();
        ui->lcdNumberPointsEquipeRouge->show();
        ui->lcdNumberPointsEquipeJaune->show();
        if(ui->entrainementAuTir->isChecked())
        {
            ui->lcdNumberPointsEquipeRouge->show();
            ui->lcdNumberPointsEquipeJaune->show();
            ui->labelPanierEquipeRouge->show();
            ui->labelPanierEquipeJaune->show();
        }
        else
        {
            ui->lcdNumberPointsEquipeRouge->hide();
            ui->lcdNumberPointsEquipeJaune->hide();
            ui->labelPanierEquipeRouge->hide();
            ui->labelPanierEquipeJaune->hide();
        }
        if(ui->puissance4->isChecked())
        {
            ui->labelVisualisationPuissance4->show();
        }
        else
        {
            ui->labelVisualisationPuissance4->hide();
        }
    }
}

/**
 * @brief Démarre une partie de basket
 *
 */
void IHM::gererPartie()
{
    qDebug() << Q_FUNC_INFO;
    initialiserPlateau();
    communication->envoyer("$basket;STT;\r");
    ui->boutonGererPartiePagePartie->setEnabled(false);
    initialiserPartie();
    demarrerChronometrePartie();
}

/**
 * @brief Slot de gestion d'une trame P (PANIER)
 */
void IHM::ajouterPanier(QString numeroPanier, QString equipe)
{
    qDebug() << Q_FUNC_INFO << numeroPanier << equipe;
    ui->lcdNumberPointsEquipeRouge->display(seance->getNbPaniersEquipeRouge());
    ui->lcdNumberPointsEquipeJaune->display(seance->getNbPaniersEquipeJaune());
    if(!seance->estFinie())
    {
        if(numeroPanier != "0")
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
        else if(numeroPanier == "0")
        {
            if(equipe == "J")
            {
                ui->labelEquipeEnCours->setText(
                  "Tir raté équipe " + seance->getNomEquipeJaune() + "!");
            }
            else if(equipe == "R")
            {
                ui->labelEquipeEnCours->setText("Tir raté pour l'équipe " +
                                                seance->getNomEquipeRouge() +
                                                "!");
            }
        }
    }

    if(seance->estFinie())
    {
        if(seance->getNbPaniersEquipeJaune() == POINT_POUR_VICTOIRE)
        {
            ui->labelEquipeEnCours->setText("Bravo à l'équipe " +
                                            seance->getNomEquipeJaune() + " !");
        }
        else if(seance->getNbPaniersEquipeRouge() == POINT_POUR_VICTOIRE)
        {
            ui->labelEquipeEnCours->setText("Bravo à l'équipe " +
                                            seance->getNomEquipeRouge() + " !");
        }
    }

    // puissance 4
    int ligne = jouerUnJeton(numeroPanier, equipe);
    qDebug() << Q_FUNC_INFO << "ligne" << ligne;
    if(ligne == -1)
        return;
    afficherUnJeton(ligne, numeroPanier.toInt(), equipe);
    if(equipe == "R")
        etatPartie = aGagne(CouleurJeton::ROUGE);
    else if(equipe == "J")
        etatPartie = aGagne(CouleurJeton::JAUNE);
    /*
     * @todo Tester l'état de la partie ou si partie nulle (estRempli())
     */
}

void IHM::afficherUnJeton(int ligne, int colonne, QString equipe)
{
    if(ui->labelVisualisationPuissance4->isHidden())
        return;
    qDebug() << Q_FUNC_INFO << ligne << colonne << equipe;
    QImage  jetonRouge(":images/jetonRouge.png");
    QImage  jetonJaune(":images/jetonJaune.png");
    QPixmap puissance4 = ui->labelVisualisationPuissance4->pixmap()
                           ->copy(); // on récupère l'image précédente
    QPainter p(&puissance4);

    if(equipe == "R")
        p.drawImage(QPoint(DEPLACEMENT_X + (colonne * TAILLE_JETON),
                           DEPLACEMENT_Y - (ligne * TAILLE_JETON)),
                    jetonRouge);
    else if(equipe == "J")
        p.drawImage(QPoint(DEPLACEMENT_X + (colonne * TAILLE_JETON),
                           DEPLACEMENT_Y - (ligne * TAILLE_JETON)),
                    jetonJaune);

    p.end();

    ui->labelVisualisationPuissance4->setPixmap(puissance4);
}

int IHM::jouerUnJeton(QString numeroPanier, QString equipe)
{
    qDebug() << Q_FUNC_INFO << numeroPanier << equipe;
    int tir = numeroPanier.toInt(); // numéro de colonne
    // on recherche la ligne
    for(int ligne = 0; ligne < plateau[tir].size(); ++ligne)
    {
        if(plateau[tir][ligne] == CouleurJeton::AUCUN)
        {
            if(equipe == "R")
                plateau[tir][ligne] = CouleurJeton::ROUGE;
            else if(equipe == "J")
                plateau[tir][ligne] = CouleurJeton::JAUNE;
            return ligne;
        }
    }

    return -1; // aucune position trouvée
}

/**
 * @brief Arrête une partie
 */
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

/**
 * @brief Gère l'horloge de durée d'une partie
 */
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

        int tempsRestantPartie = seance->getDureeTempsPartie();
        if(tempsRestantPartie > 0)
        {
            ui->tempsPartie->setText(QString::number(tempsRestantPartie) +
                                     QString(" m"));
        }
    }
}

/**
 * @brief Démarre le chronomètrage d'une partie
 */
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

/**
 * @brief Arrête le chronométrage d'une partie
 */
void IHM::arreterChronometrePartie()
{
    if(chronometrePartie != nullptr && chronometrePartie->isActive())
        chronometrePartie->stop();
}

/**
 * @brief Gère le chronométrage d'une partie
 */
void IHM::gererChronometrePartie()
{
    QTime tempsChronometre(0, 0);
    tempsChronometre = tempsChronometre.addMSecs(tempsEcoulePartie.elapsed());
    /**
     * @todo TODO Gérer le temps d'une partie et d'un tir
     */
    afficherChronometrePartie(tempsChronometre.toString("mm:ss"));
}

/**
 * @brief Affiche la durée de la partie en cours
 */
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

/**
 * @brief Affiche la page principale
 */
void IHM::afficherPagePrincipale()
{
    arreterPartie();
    afficherFenetre(IHM::PagePrincipale);
}

/**
 * @brief Affiche la page des règles
 */
void IHM::afficherPageRegles()
{
    afficherFenetre(IHM::PageRegles);
}

/**
 * @brief Affiche la page configuration
 */
void IHM::afficherPageConfiguration()
{
    if(seance != nullptr)
        arreterPartie();
    afficherFenetre(IHM::PageConfiguration);
}

/**
 * @brief Affiche la page partie
 */
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

/**
 * @brief Connecte un module Bluetooth
 */
void IHM::gererPeripherique(QString nom, QString adresseMAC)
{
    qDebug() << Q_FUNC_INFO << nom << adresseMAC;
    communication->connecter();
}

/**
 * @brief Affiche l'état de connexion du module Bluetooth
 */
void IHM::afficherEtatConnexion()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Affiche l'état de déconnexion du module Bluetooth
 */
void IHM::afficherEtatDeconnexion()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Termine la recherche des modules Bluetooth
 */
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

    for(int i = 0; i < plateau.size(); ++i)
    {
        plateau[i].resize(NB_LIGNES);
    }
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

/**
 * @brief Récupère les équipes dans la base de données
 */
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

/**
 * @brief Ajoute
 */
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

/**
 * @brief Affiche les équipes dans les listes déroulantes
 */
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

/**
 * @brief Initialise une nouvelle partie
 */
void IHM::initialiserPartie()
{
    seance->setNbPaniersEquipeJaune(0);
    seance->setNbPaniersEquipeRouge(0);
    seance->setDebutTemps(QTime::currentTime());
    seance->setDebutTempsTour(QTime::currentTime());
    timerSeance->start(500);
}

/*
void IHM::afficherPuissance4(QString numeroPanier, QString equipe)
{
    QImage  jetonRouge(":images/jetonRouge.png");
    QImage  jetonJaune(":images/jetonJaune.png");
    QPixmap plateau = ui->labelVisualisationPuissance4->pixmap()
                        ->copy(); // on récupère l'image précédente
    QPainter p(&plateau);
    p.drawImage(
      QPoint(DEPLACEMENT_LIGNE + (1 * 60), DEPLACEMENT_COLONNE - (1 * 60)),
      jetonJaune);

    if(!seance->estFinie() && equipe == "R")
    {
        if(numeroPanier == "1")
        {
            seance->setColonne(0);
        }
        // Si plus de place dans le puissance 4 dans la 1er colonne
        if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() == 6)
            return;

        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    5)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (5 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 0 ligne 5";
        }

        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    4)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (4 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 0 ligne 4";
        }
        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    3)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (3 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 0 ligne 3";
        }
        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    2)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (2 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 0 ligne 2";
        }

        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    1)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (1 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 0 ligne 1";
        }
        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    0)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (0 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 0 ligne 0";
        }

        if(!seance->estFinie())
        {
            if(numeroPanier == "2")
            {
                seance->setColonne(1);
            }
            // Si plus de place dans le puissance 4 dans la 2eme colonne
            if(seance->getColonne() == 1 && seance->getNbrJetonColonne1() ==
    6) return;

            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 5)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (5 * 60)),
                  jetonRouge);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton rouge colonne 1 ligne 5";
            }

            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 4)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (4 * 60)),
                  jetonRouge);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton rouge colonne 1 ligne 4";
            }
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 3)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (3 * 60)),
                  jetonRouge);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton rouge colonne 1 ligne 3";
            }
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 2)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (2 * 60)),
                  jetonRouge);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton rouge colonne 1 ligne 2";
            }

            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 1)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (1 * 60)),
                  jetonRouge);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton rouge colonne 1 ligne 1";
            }
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 0)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (0 * 60)),
                  jetonRouge);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton rouge colonne 1 ligne 0";
            }
        }

        if(numeroPanier == "3")
        {
            seance->setColonne(2);
        }
        // Si plus de place dans le puissance 4 dans la 3eme colonne
        if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() == 6)
            return;

        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    5)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (5 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 2 ligne 5";
        }

        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    4)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (4 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 2 ligne 4";
        }
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    3)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (3 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 2 ligne 3";
        }
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    2)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (2 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 2 ligne 2";
        }

        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    1)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (1 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 2 ligne 1";
        }
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    0)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (0 * 60)), jetonRouge);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton rouge colonne 2 ligne 0";
        }
    }

    if(numeroPanier == "4")
    {
        seance->setColonne(3);
    }
    // Si plus de place dans le puissance 4 dans la 3eme colonne
    if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 6)
        return;

    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 5)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (5 * 60)),
                    jetonRouge);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton rouge colonne 3 ligne 5";
    }

    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 4)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (4 * 60)),
                    jetonRouge);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton rouge colonne 3 ligne 4";
    }
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 3)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (3 * 60)),
                    jetonRouge);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton rouge colonne 3 ligne 3";
    }
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 2)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (2 * 60)),
                    jetonRouge);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton rouge colonne 3 ligne 2";
    }

    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 1)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (1 * 60)),
                    jetonRouge);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton rouge colonne 3 ligne 1";
    }
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 0)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (0 * 60)),
                    jetonRouge);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton rouge colonne 3 ligne 0";
    }

    if(!seance->estFinie() && equipe == "J")
    {
        if(numeroPanier == "1")
        {
            seance->setColonne(0);
        }
        // Si plus de place dans le puissance 4 dans la 1er colonne
        if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() == 6)
            return;

        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    5)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (5 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 4 ligne 5";
        }

        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    4)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (4 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 4 ligne 4";
        }
        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    3)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (3 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 4 ligne 3";
        }
        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    2)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (2 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 4 ligne 2";
        }

        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    1)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (1 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 4 ligne 1";
        }
        else if(seance->getColonne() == 0 && seance->getNbrJetonColonne0() ==
    0)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (0 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne0();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 4 ligne 0";
        }

        {
            if(numeroPanier == "2")
            {
                seance->setColonne(1);
            }
            // Si plus de place dans le puissance 4 dans la 2eme colonne
            if(seance->getColonne() == 1 && seance->getNbrJetonColonne1() ==
    6) return;
            // Verification si 5 jeton dans la colonne 2
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 5)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (5 * 60)),
                  jetonJaune);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton jaune colonne 2 ligne 5";
            }
            // Verification si 5 jeton dans la colonne 2
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 4)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (4 * 60)),
                  jetonJaune);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton jaune colonne 3 ligne 4";
            }
            // Verification si 4 jeton dans la colonne 1
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 3)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (3 * 60)),
                  jetonJaune);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton jaune colonne 3 ligne 3";
            }
            // Verification si 3 jeton dans la colonne 1
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 2)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (2 * 60)),
                  jetonJaune);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton jaune colonne 3 ligne 2";
            }

            // Verification si 2 jeton dans la colonne 1
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 1)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (1 * 60)),
                  jetonJaune);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton jaune colonne 3 ligne 1";
            }
            // Verification si 0 jeton dans la colonne 1
            else if(seance->getColonne() == 1 &&
                    seance->getNbrJetonColonne1() == 0)
            {
                p.drawImage(
                  QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                         DEPLACEMENT_COLONNE - (0 * 60)),
                  jetonJaune);
                seance->augmenterNbrJetonColonne1();
                qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                         << "un jeton jaune colonne 3 ligne 0";
            }
        }

        if(numeroPanier == "3")
        {
            seance->setColonne(2);
        }
        // Si plus de place dans le puissance 4 dans la colonne 2
        if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() == 6)
            return;
        // Verification si 4 jeton dans la colonne 2
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    5)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (5 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 2 ligne 5";
        }
        // Verification si 3 jeton dans la colonne 2
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    4)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (4 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 2 ligne 4";
        }
        // Verification si 3 jeton dans la colonne 2
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    3)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (3 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 2 ligne 3";
        }
        // Verification si 2 jeton dans la colonne 2
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    2)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (2 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 2 ligne 2";
        }
        // Verification si 1 jeton dans la colonne 2
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    1)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (1 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 2 ligne 1";
        }
        // Verification si 0 jeton dans la colonne 2
        else if(seance->getColonne() == 2 && seance->getNbrJetonColonne2() ==
    0)
        {
            p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() *
    60), DEPLACEMENT_COLONNE - (0 * 60)), jetonJaune);
            seance->augmenterNbrJetonColonne2();
            qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                     << "un jeton jaune colonne 2 ligne 0";
        }
    }

    if(numeroPanier == "4")
    {
        seance->setColonne(3);
    }
    // Si plus de place dans le puissance 4 dans la colonne 3
    if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 6)
        return;
    // Verification si 5 jeton dans la colonne 3
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 5)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (5 * 60)),
                    jetonJaune);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton jaune colonne 4 ligne 5";
    }
    // Verification si 4 jeton dans la colonne 3
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 4)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (4 * 60)),
                    jetonJaune);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton jaune colonne 4 ligne 4";
    }
    // Verification si 3 jeton dans la colonne 3
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 3)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (3 * 60)),
                    jetonJaune);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton jaune colonne 4 ligne 3";
    }
    // Verification si 2 jeton dans la colonne 3
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 2)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (2 * 60)),
                    jetonJaune);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton jaune colonne 4 ligne 2";
    }
    // Verification si 1 jeton dans la colonne 3
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 1)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (1 * 60)),
                    jetonJaune);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton jaune colonne 4 ligne 1";
    }
    // Verification si 0 jeton dans la colonne 3
    else if(seance->getColonne() == 3 && seance->getNbrJetonColonne3() == 0)
    {
        p.drawImage(QPoint(DEPLACEMENT_LIGNE + (seance->getColonne() * 60),
                           DEPLACEMENT_COLONNE - (0 * 60)),
                    jetonJaune);
        seance->augmenterNbrJetonColonne3();
        qDebug() << Q_FUNC_INFO << "colonne" << seance->getColonne()
                 << "un jeton jaune colonne 4 ligne 0";
    }
    p.end();

    ui->labelVisualisationPuissance4->setPixmap(plateau);
}
*/

void IHM::afficherPlateau()
{
    ui->labelVisualisationPuissance4->setPixmap(QPixmap(":/puissance4.png"));
}

void IHM::initialiserPlateau()
{
    qDebug() << Q_FUNC_INFO << plateau.size() << plateau[0].size();

    for(int colonne = 0; colonne < plateau.size(); ++colonne)
    {
        for(int ligne = 0; ligne < plateau[colonne].size(); ++ligne)
        {
            plateau[colonne][ligne] = CouleurJeton::AUCUN;
        }
    }

    etatPartie = false;

    afficherPlateau();
}

IHM::CouleurJeton IHM::verifierLigne(int ligne)
{
    // horizontalement ?
    int somme = 0;
    for(int colonne = 0; colonne <= (NB_PANIERS - NB_PIONS_ALIGNES); ++colonne)
    {
        somme = plateau[colonne][ligne] + plateau[colonne + 1][ligne] +
                plateau[colonne + 2][ligne] + plateau[colonne + 3][ligne];
        if(somme == NB_PIONS_ALIGNES)
        {
            return CouleurJeton::JAUNE;
        }
        else if(somme == NB_PIONS_ALIGNES * -1)
        {
            return CouleurJeton::ROUGE;
        }
    }

    return CouleurJeton::AUCUN;
}

IHM::CouleurJeton IHM::verifierDiagonales()
{
    // diagonalement
    int somme = 0;
    for(int ligne = 0; ligne <= (NB_LIGNES - NB_PIONS_ALIGNES); ++ligne)
    {
        for(int colonne = 0; colonne <= (NB_PANIERS - NB_PIONS_ALIGNES);
            ++colonne)
        {
            somme = plateau[colonne][ligne] + plateau[colonne + 1][ligne + 1] +
                    plateau[colonne + 2][ligne + 2] +
                    plateau[colonne + 3][ligne + 3];
            if(somme == NB_PIONS_ALIGNES)
            {
                return CouleurJeton::JAUNE;
            }
            else if(somme == NB_PIONS_ALIGNES * -1)
            {
                return CouleurJeton::ROUGE;
            }
        }
    }
    return CouleurJeton::AUCUN;
}

bool IHM::aGagne(CouleurJeton couleurEquipe)
{
    // horizontalement
    for(int ligne = 0; ligne < NB_LIGNES; ++ligne)
    {
        CouleurJeton couleur = verifierLigne(ligne);
        if(couleur == couleurEquipe)
        {
            return true;
        }
    }

    return false;
}

bool IHM::estRempli()
{
    // for()
    if(CouleurJeton::AUCUN)
        return false;

    return true;
}
