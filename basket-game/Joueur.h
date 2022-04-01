#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>

class Joueur
{
    private:
        QString pseudo;
        QString nom;
        QString prenom;

    public:
        Joueur(QString pseudo ="",QString nom ="",QString prenom="");
        ~Joueur();
        Joueur& operator=(const Joueur&);

        QString getPseudo() const;
        void    setPseudo(const QString& pseudo);

        QString getNom () const;
        void    setNom (const QString& nom);

        QString getPrenom() const;
        void    setPrenom(const QString& prenom);
};

#endif // JOUEUR_H
