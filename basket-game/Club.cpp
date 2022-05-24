#include "Club.h"

Club::Club(QString nomClub /*""*/) : nomClub(nomClub)
{
}

Club::~Club()
{
}

Club& Club::operator=(const Club& c)
{
    if(this != &c)
    {
        nomClub = c.nomClub;
    }
    return *this;
}

QString Club::getNomClub() const
{
    return nomClub;
}

void Club::setNomClub(const QString& nomClub)
{
    this->nomClub = nomClub;
}
