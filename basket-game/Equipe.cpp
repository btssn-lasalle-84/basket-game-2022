#include "Equipe.h"
#include "Joueur.h"
#include <QDebug>

Equipe::Equipe(QString nomEquipe /*=""*/,
               int     nbrPointEquipeRouge,
               int     nbrPointEquipeJaune) :
    nomEquipe(nomEquipe),
    nbrPointEquipeRouge(nbrPointEquipeRouge),
    nbrPointEquipeJaune(nbrPointEquipeJaune)
{
    qDebug() << Q_FUNC_INFO << this;
}

Equipe::~Equipe()
{
    for(int i = 0; i < joueurs.size(); ++i)
        delete joueurs[i];
    qDebug() << Q_FUNC_INFO << this;
}

Equipe& Equipe::operator=(const Equipe& e)
{
    if(this != &e)
    {
        nomEquipe           = e.nomEquipe;
        nbrPointEquipeRouge = e.nbrPointEquipeRouge;
        nbrPointEquipeJaune = e.nbrPointEquipeJaune;
    }
    return *this;
}

QString Equipe::getNomEquipe() const
{
    return nomEquipe;
}

void Equipe::setNomEquipe(const QString& nomEquipe)
{
    this->nomEquipe = nomEquipe;
    qDebug() << Q_FUNC_INFO << nomEquipe;
}

int Equipe::getNbrPointEquipeRouge() const
{
    return nbrPointEquipeRouge;
}

void Equipe::setNbrPointEquipeRouge(const int& nbrPointEquipeRouge)
{
    this->nbrPointEquipeRouge = getNbrPointEquipeRouge();
}

int Equipe::getNbrPointEquipeJaune() const
{
    return nbrPointEquipeJaune;
}

void Equipe::setNbrPointEquipeJaune(const int& nbrPointEquipeJaune)
{
    this->nbrPointEquipeJaune = nbrPointEquipeJaune;
}

void Equipe::supprimerJoueurs()
{
    for(int i = 0; i < joueurs.size(); ++i)
        delete joueurs[i];
    joueurs.clear();
}

void Equipe::ajouterJoueur(QString idJoueur)
{
    qDebug() << Q_FUNC_INFO << "idJoueur" << idJoueur;
    /**
     * @todo récupérer le joueur dans la base de données, instancier un nouveau
     * Joueur et l'ajouter au conteneur
     */
    joueurs.push_back(new Joueur);
}
