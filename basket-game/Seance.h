#ifndef SEANCE_H
#define SEANCE_H

#include <QTime>
#include <QTimer>

class Equipe;

/**
 * @def POINT_POUR_VICTOIRE
 * @brief Constante des points pour une victoire
 */
#define POINT_POUR_VICTOIRE 4

class Seance : public QObject
{
    Q_OBJECT
  private:
    int     numeroManche;
    Equipe* equipeJaune;
    Equipe* equipeRouge;
    int     nbPaniersEquipeJaune;
    int     nbPaniersEquipeRouge;
    QTime   debutTemps;
    QTime   finTemps;
    QTimer* timer;

  public:
    Seance(Equipe* equipeJaune = nullptr, Equipe* equipeRouge = nullptr);
    ~Seance();

    int     getNumeroManche() const;
    void    setNumeroManche(const int&);
    int     getNbPaniersEquipeJaune() const;
    void    setNbPaniersEquipeJaune(const int&);
    int     getNbPaniersEquipeRouge() const;
    void    setNbPaniersEquipeRouge(const int&);
    QTime   getDebutTemps() const;
    void    setDebutTemps(const QTime&);
    QTime   getFinTemps() const;
    void    setFinTemps(const QTime&);
    void    marquerUnPointEquipeJaune();
    void    marquerUnPointEquipeRouge();
    QString getNomEquipeJaune() const;
    void    setNomEquipeJaune(const QString&);
    QString getNomEquipeRouge() const;
    void    setNomEquipeRouge(const QString&);
    bool    estFinie();
};

#endif // SEANCE_H
