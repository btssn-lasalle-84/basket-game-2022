#ifndef SEANCE_H
#define SEANCE_H

#include <QTime>

/**
 * @def POINT_POUR_VICTOIRE
 * @brief Constante des points pour une victoire

 */
#define POINT_POUR_VICTOIRE 4

class Seance
{
  private:
    int   numeroManche;
    int   nbPaniersEquipeA;
    int   nbPaniersEquipeB;
    QTime debutTemps;
    QTime finTemps;

  public:
    Seance(int   numeroManche     = 0,
           int   nbPaniersEquipeA = 0,
           int   nbPaniersEquipeB = 0,
           QTime debutTemps       = QTime(),
           QTime finTemps         = QTime());
    Seance(const Seance&);
    ~Seance();
    Seance& operator=(const Seance&);

    int   getNumeroManche() const;
    void  setNumeroManche(const int&);
    int   getNbPaniersEquipeA() const;
    void  setNbPaniersEquipeA(const int&);
    int   getNbPaniersEquipeB() const;
    void  setNbPaniersEquipeB(const int&);
    QTime getDebutTemps() const;
    void  setDebutTemps(const QTime&);
    QTime getFinTemps() const;
    void  setFinTemps(const QTime&);
    void  marquerUnPointEquipeJaune();
    void  marquerUnPointEquipeRouge();

    bool estFinie();
};

#endif // SEANCE_H
