#include "Equipe.h"

Equipe::Equipe(QString nomEquipe /*=""*/,
               int     nbrPointEquipeRouge,
               int     nbrPointEquipeJaune) :
    nomEquipe(nomEquipe),
    nbrPointEquipeRouge(nbrPointEquipeRouge),
    nbrPointEquipeJaune(nbrPointEquipeJaune)
{
}

Equipe::~Equipe()
{
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
