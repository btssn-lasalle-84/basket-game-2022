#ifndef EQUIPE_H
#define EQUIPE_H

#include <QString>

class Equipe
{
  private:
    QString nomEquipe;
    int     nbrPointEquipeRouge;
    int     nbrPointEquipeJaune;

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
};

#endif // EQUIPE_H
