#include "Seance.h"

Seance::Seance()
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

int Seance::getNbPaniersEquipeA() const
{
    return nbPaniersEquipeA;
}

void Seance::setNbPaniersEquipeA(const int& NbPaniersEquipeA)
{
    this->NbPaniersEquipeA = NbPaniersEquipeA;
}

int Seance::getNbPaniersEquipeB() const
{
    return nbPaniersEquipeB;
}

void Seance::setNbPaniersEquipeB(const int& NbPaniersEquipeB)
{
    this->NbPaniersEquipeB = NbPaniersEquipeB;
}

