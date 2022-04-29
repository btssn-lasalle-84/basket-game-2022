#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QString>
#include <QBluetoothServer>
#include <QBluetoothLocalDevice>

/**
 * @brief
 * Definition de la trame
 */
#define TYPE_TRAME "$basket"

/**
 * @brief
 * Delimiteur de fin de fin de trame
 */
#define DELIMITEUR_FIN "\r"

static const QString serviceUuid(
  QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
static const QString serviceNom(QStringLiteral("BasketGame"));

class Communication : public QObject

{
  private:
    QBluetoothServer*     serveur;
    QBluetoothSocket*     socket;
    QBluetoothServiceInfo serviceInfo;
    QBluetoothLocalDevice peripheriqueLocal;
    bool                  connecte;

  public:
    Communication();
    ~Communication();

    void demarrer();
    void arreter();
    void nouveauClient();
    void decomposerTrame();
    bool trameEstValide();
};

#endif // COMMUNICATION_H
