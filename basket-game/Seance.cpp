#include "Seance.h"
#include "QDebug"
Seance::Seance(int   numeroManche /*=0*/,
               int   nbPaniersEquipeA /*=0*/,
               int   nbPaniersEquipeB /*=0*/,
               QTime debutTemps /*=0*/,
               QTime finTemps /*=0*/) :
    numeroManche(numeroManche),
    nbPaniersEquipeA(nbPaniersEquipeA), nbPaniersEquipeB(nbPaniersEquipeB),
    debutTemps(debutTemps), finTemps(finTemps)

{
}

Seance::Seance(const Seance& s) :
    numeroManche(s.numeroManche), nbPaniersEquipeA(s.nbPaniersEquipeA),
    nbPaniersEquipeB(s.nbPaniersEquipeB), debutTemps(s.debutTemps),
    finTemps(s.finTemps)
{
}

Seance::~Seance()
{
}

Seance& Seance::operator=(const Seance& s)
{
    if(this != &s)
    {
        this->numeroManche     = s.numeroManche;
        this->nbPaniersEquipeA = s.nbPaniersEquipeA;
        this->nbPaniersEquipeB = s.nbPaniersEquipeB;
        this->debutTemps       = s.debutTemps;
        this->finTemps         = s.finTemps;
    }
    return *this;
}

int Seance::getNumeroManche() const
{
    return numeroManche;
}

void Seance::setNumeroManche(const int& numeroManche)
{
    this->numeroManche = numeroManche;
}

int Seance::getNbPaniersEquipeA() const
{
    return nbPaniersEquipeA;
}

void Seance::setNbPaniersEquipeA(const int& NbPaniersEquipeA)
{
    this->nbPaniersEquipeA = NbPaniersEquipeA;
}

int Seance::getNbPaniersEquipeB() const
{
    return nbPaniersEquipeB;
}

void Seance::setNbPaniersEquipeB(const int& NbPaniersEquipeB)
{
    this->nbPaniersEquipeB = NbPaniersEquipeB;
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

void Seance::marquerUnPointEquipeJaune()
{
    nbPaniersEquipeB = this->nbPaniersEquipeA + 1;
}

void Seance::marquerUnPointEquipeRouge()
{
    nbPaniersEquipeB = this->nbPaniersEquipeB + 1;
}

bool Seance::estFinie()
{
    if((getNbPaniersEquipeA() == POINT_POUR_VICTOIRE) ||
       (getNbPaniersEquipeB() == POINT_POUR_VICTOIRE))
    {
        return true;
    }
    return false;
}
