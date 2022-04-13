#ifndef EQUIPE_H
#define EQUIPE_H

#include <QString>
#include <QList>

class Joueur;

class Equipe
{
  private:
    QString        nomEquipe;
    int            nbrPointEquipeRouge;
    int            nbrPointEquipeJaune;
    QList<Joueur*> joueurs;

  public:
    Equipe(QString nomEquipe        = "",
           int     pointEquipeRouge = 0,
           int     pointEquipeJaune = 0);
    ~Equipe();
    Equipe& operator=(const Equipe&);

    QString getNomEquipe() const;
    void    setNomEquipe(const QString& nomEquipe);

    int  getNbrPointEquipeRouge() const;
    void setNbrPointEquipeRouge(const int& nbrPointEquipeRouge);

    int  getNbrPointEquipeJaune() const;
    void setNbrPointEquipeJaune(const int& nbrPointEquipeJaune);

    void supprimerJoueurs();
    void ajouterJoueur(QString idJoueur);
};

#endif // EQUIPE_H
