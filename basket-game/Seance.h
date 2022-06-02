#ifndef SEANCE_H
#define SEANCE_H

#include <QObject>
#include <QTime>

class Equipe;

/**
 * @def POINT_POUR_VICTOIRE
 * @brief Constante des points pour une victoire
 */
#define POINT_POUR_VICTOIRE 15

/**
 * @def TEMPS_PAR_TOUR_DEFAUT
 * @brief Le temps pour un tour
 */
#define TEMPS_PAR_TOUR_DEFAUT   30 // en s
#define TEMPS_PAR_PARTIE_DEFAUT 3  // en m

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
    QTime   debutTempsTour;
    int     dureeTempsTour;
    int     dureeTempsPartie;
    int     colonne;
    int     ligne;
    int     nbrJetonColonne0;

  public:
    Seance(Equipe*  equipeJaune = nullptr,
           Equipe*  equipeRouge = nullptr,
           QObject* parent      = nullptr);
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
    QTime   getDebutTempsTour() const;
    void    setDebutTempsTour(const QTime&);
    int     getDureeTempsTour() const;
    void    setDureeTempsTour(int);
    int     getDureeTempsPartie() const;
    void    setDureeTempsPartie(int);
    void    marquerUnPointEquipeJaune();
    void    marquerUnPointEquipeRouge();
    QString getNomEquipeJaune() const;
    void    setNomEquipeJaune(const QString&);
    QString getNomEquipeRouge() const;
    void    setNomEquipeRouge(const QString&);
    int     getColonne() const;
    void    setColonne(const int&);
    int     getLigne() const;
    void    setLigne(const int&);
    int     getNbrJetonColonne0() const;
    void    augmenterNbrJetonColonne0();
    bool    estFinie();
};

#endif // SEANCE_H
