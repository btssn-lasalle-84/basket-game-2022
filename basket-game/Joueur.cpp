#include "Joueur.h"

Joueur::Joueur(QString pseudo/*=""*/, QString nom/*=""*/,QString prenom/*=""*/) : pseudo(pseudo),nom(nom),prenom(prenom)
{
}

Joueur& Joueur::operator=(const Joueur& j)
{
    if(this != &j)
    {
        pseudo = j.pseudo;
    }
    return *this;
}

Joueur::~Joueur()
{
}

QString Joueur::getPseudo() const
{
    return pseudo;
}

void Joueur::setPseudo(const QString& pseudo)
{
    this->pseudo = pseudo;
}

QString Joueur::getNom() const
{
    return nom;
}

void Joueur::setNom(const QString& nom)
{
    this->nom = nom;
}

QString Joueur::getPrenom() const
{
    return prenom;
}

void Joueur::setPrenom(const QString& prenom)
{
    this->prenom = prenom;
}
