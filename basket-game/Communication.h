#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QString>
#include <QtBluetooth>

/**
 * @def ENTETE_NOM_PERIPHERIQUE
 * @brief Définition du préfixe du nom de périphérique bluetooth
 */
#define ENTETE_NOM_PERIPHERIQUE "b4sket-game"

/**
 * @def TYPE_TRAME
 * @brief Définition de l'entête de trame
 */
#define TYPE_TRAME "$basket"

/**
 * @def DELIMITEUR_FIN
 * @brief Délimiteur de fin de fin de trame
 */
#define DELIMITEUR_FIN "\r"

static const QString serviceUuid(
  QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
static const QString serviceNom(QStringLiteral("BasketGame"));

class Communication : public QObject
{
    Q_OBJECT
  private:
    QBluetoothSocket* socket; //!< socket de communication bluetooth (client)
    QBluetoothServiceInfo
      serviceInfo; //!< informations sur le service bluetooth
    QBluetoothDeviceDiscoveryAgent*
                          discoveryAgent; //!< agent de détection des périphériques
    QBluetoothLocalDevice peripheriqueLocal;   //!< interface Bluetooth locale
    QBluetoothDeviceInfo  peripheriqueDistant; //!< Le module Bluetooth GROOM
    bool    peripheriqueTrouve; //!< periphérique distant trouvé ou non
    QString trameReception;     //!< la trame de reception

    void initialiser();
    bool estBluetoothPresent() const;
    void decomposerTrame();

  public:
    Communication(QObject* parent = nullptr);
    ~Communication();

    void rechercher();
    void connecter();
    void deconnecter();
    bool estConnecte() const;
    bool estPeripheriqueTrouve() const;
    void envoyer(QString trame);

  public slots:
    void decouvrirPeripherique(const QBluetoothDeviceInfo& device);
    void terminerRecherche();
    void receptionnerTrame();

  signals:
    void peripheriqueDetecte(QString nom, QString adresseMAC);
    void rechercheTerminee();
    void peripheriqueConnecte();
    void peripheriqueDeconnecte();
};

#endif // COMMUNICATION_H
