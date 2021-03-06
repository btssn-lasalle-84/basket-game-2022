#include "Seance.h"
#include "Equipe.h"
#include "QDebug"
#include "IHM.h"

Seance::Seance(Equipe*  equipeJaune /*= nullptr*/,
               Equipe*  equipeRouge /*= nullptr*/,
               QObject* parent /*= nullptr*/) :
    QObject(parent),
    numeroManche(0), equipeJaune(equipeJaune), equipeRouge(equipeRouge),
    nbPaniersEquipeJaune(0), nbPaniersEquipeRouge(0),
    debutTemps(QTime::currentTime()), finTemps(QTime()),
    debutTempsTour(QTime()), dureeTempsTour(5)
{
}

Seance::~Seance()
{
}

int Seance::getNumeroManche() const
{
    return numeroManche;
}

void Seance::setNumeroManche(const int& numeroManche)
{
    this->numeroManche = numeroManche;
}

int Seance::getNbPaniersEquipeJaune() const
{
    return nbPaniersEquipeJaune;
}

void Seance::setNbPaniersEquipeJaune(const int& nbPaniersEquipeJaune)
{
    this->nbPaniersEquipeJaune = nbPaniersEquipeJaune;
}

int Seance::getNbPaniersEquipeRouge() const
{
    return nbPaniersEquipeRouge;
}

void Seance::setNbPaniersEquipeRouge(const int& NbPaniersEquipeRouge)
{
    this->nbPaniersEquipeRouge = NbPaniersEquipeRouge;
}

QTime Seance::getDebutTemps() const
{
    return debutTemps;
}

void Seance::setDebutTemps(const QTime& debutTemps)
{
    this->debutTemps = debutTemps;
}

QTime Seance::getFinTemps() const
{
    return finTemps;
}

void Seance::setFinTemps(const QTime& finTemps)
{
    this->finTemps = finTemps;
}

QTime Seance::getDebutTempsTour() const
{
    return debutTempsTour;
}

void Seance::setDebutTempsTour(const QTime& debutTempsTour)
{
    QTime nouveauDebutTempsTour = debutTempsTour.addSecs(dureeTempsTour);
    this->debutTempsTour        = nouveauDebutTempsTour;
}

int Seance::getDureeTempsTour() const
{
    return dureeTempsTour;
}

void Seance::setDureeTempsTour(int dureeTempsTour)
{
    this->dureeTempsTour = dureeTempsTour;
}

int Seance::getDureeTempsPartie() const
{
    return dureeTempsPartie;
}

void Seance::setDureeTempsPartie(int dureeTempsPartie)
{
    this->dureeTempsPartie = dureeTempsPartie;
}

void Seance::marquerUnPointEquipeJaune()
{
    nbPaniersEquipeJaune = this->nbPaniersEquipeJaune + 1;
}

void Seance::marquerUnPointEquipeRouge()
{
    nbPaniersEquipeRouge = this->nbPaniersEquipeRouge + 1;
}

QString Seance::getNomEquipeJaune() const
{
    return equipeJaune->getNomEquipe();
}

void Seance::setNomEquipeJaune(const QString& nomEquipeJaune)
{
    this->equipeJaune->setNomEquipe(nomEquipeJaune);
}

QString Seance::getNomEquipeRouge() const
{
    return equipeRouge->getNomEquipe();
}

void Seance::setNomEquipeRouge(const QString& nomEquipeRouge)
{
    this->equipeRouge->setNomEquipe(nomEquipeRouge);
}

bool Seance::estFinie()
{
    if((getNbPaniersEquipeJaune() == POINT_POUR_VICTOIRE) ||
       (getNbPaniersEquipeRouge() == POINT_POUR_VICTOIRE))
    {
        return true;
    }
    return false;
}
