#ifndef SEANCE_H
#define SEANCE_H

#include <QTime>

class Seance
{
    private:
    int numeroManche;
    int nbPaniersEquipeA;
    int nbPaniersEquipeB;
    QTime debut();
    QTime fin;

    public:
        Seance();
        ~Seance();

        int getNumeroManche() const;
        void setNumeroManche(const int&);

        int getNbPaniersEquipeA() const;
        void setNbPaniersEquipeA(const int&);

        int getNbPaniersEquipeB() const;
        void setNbPaniersEquipeB(const int&);

};

#endif // SEANCE_H
