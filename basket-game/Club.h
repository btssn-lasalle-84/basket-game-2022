#ifndef CLUB_H
#define CLUB_H

#include <QString>

class Club
{
  private:
    QString nomClub;

  public:
    Club(QString nomClub = "");
    ~Club();
    Club& operator=(const Club&);

    QString getNomClub() const;
    void    setNomClub(const QString& nomClub);
};

#endif // CLUB_H
