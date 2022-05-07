#include "Communication.h"
#include "Seance.h"
#include <QDebug>

Communication::Communication(QObject* parent) :
    QObject(parent), socket(nullptr), discoveryAgent(nullptr),
    peripheriqueTrouve(false)
{
    qDebug() << Q_FUNC_INFO;

    initialiser();
}

Communication::~Communication()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Méthode de recherche des périphériques bluetooth
 */
void Communication::rechercher()
{
    // vérifie la présence du bluetooth
    if(!estBluetoothPresent())
        return;

    if(discoveryAgent == nullptr)
        return;

    qDebug() << Q_FUNC_INFO;

    // démarre la recherche de périphériques bluetooth
    peripheriqueTrouve = false;
    discoveryAgent->start();
}

/**
 * @brief Méthode qui permet de se connecter au périphérique
 */
void Communication::connecter()
{
    // vérifie la présence du bluetooth
    if(!estBluetoothPresent())
        return;
    // vérifie si le périphérique est déjà connecté
    if(estConnecte())
        return;
    // vérifie si le périphérique a été trouvé
    if(!estPeripheriqueTrouve())
        return;

    // prépare la socket bluetooth
    if(socket == nullptr)
    {
        socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        connect(socket,
                SIGNAL(connected()),
                this,
                SIGNAL(peripheriqueConnecte()));
        connect(socket,
                SIGNAL(disconnected()),
                this,
                SIGNAL(peripheriqueDeconnecte()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(receptionnerTrame()));
    }

    qDebug() << Q_FUNC_INFO << peripheriqueDistant.name()
             << peripheriqueDistant.address().toString();

    // assure la connexion
    QBluetoothAddress adresse =
      QBluetoothAddress(peripheriqueDistant.address());
    QBluetoothUuid uuid = QBluetoothUuid(QBluetoothUuid::SerialPort);
    socket->connectToService(adresse, uuid);
    socket->open(QIODevice::ReadWrite);
}

/**
 * @brief Méthode de déconnexion bluetooth
 */
void Communication::deconnecter()
{
    // vérifie la présence du bluetooth
    if(!estBluetoothPresent())
        return;
    // vérifie la socket bluetooth
    if(socket == nullptr)
        return;
    // vérifie si le périphérique est connecté
    if(estConnecte())
        socket->close();

    qDebug() << Q_FUNC_INFO << peripheriqueDistant.name()
             << peripheriqueDistant.address().toString();
}

/**
 * @brief Retourne l'état de connexion
 */
bool Communication::estConnecte() const
{
    // vérifie la présence du bluetooth
    if(!estBluetoothPresent())
        return false;
    // vérifie la socket bluetooth
    if(socket == nullptr)
        return false;
    qDebug() << Q_FUNC_INFO << socket->isOpen();
    return socket->isOpen();
}

/**
 * @brief Retourne l'état de la recherche
 */
bool Communication::estPeripheriqueTrouve() const
{
    return peripheriqueTrouve;
}

/**
 * @brief Méthode d'envoi de trame
 */
void Communication::envoyer(QString trame)
{
    // vérifie la présence du bluetooth
    if(!estBluetoothPresent())
        return;
    // vérifie la connexion du périphrique
    if(!estConnecte())
        return;
    qDebug() << Q_FUNC_INFO << trame;
    socket->write(trame.toLocal8Bit());
}

/**
 * @brief Slot qui permet de rechercher le périphérique distant
 */
void Communication::decouvrirPeripherique(const QBluetoothDeviceInfo& device)
{
    qDebug() << Q_FUNC_INFO << device.name() << device.address().toString();
    if(device.name().startsWith(ENTETE_NOM_PERIPHERIQUE))
    {
        qDebug() << Q_FUNC_INFO << "périphérique trouvé !";
        discoveryAgent->stop();
        peripheriqueDistant = device;
        peripheriqueTrouve  = true;
        emit peripheriqueDetecte(device.name(), device.address().toString());
        discoveryAgent->stop();
        terminerRecherche();
    }
}

/**
 * @brief Slot de fin de recherche des périphériques
 */
void Communication::terminerRecherche()
{
    qDebug() << Q_FUNC_INFO;
    emit rechercheTerminee();
}

/**
 * @brief Slot de reception de trame
 */
void Communication::receptionnerTrame()
{
    QByteArray donnees;

    // récupère les données reçues
    donnees = socket->readAll();
    // qDebug() << Q_FUNC_INFO << donnees;

    // ajoute les données reçues
    trameReception += QString(donnees.data());
    qDebug() << Q_FUNC_INFO << trameReception;

    // vérifie si la trame est valide
    if(trameReception.startsWith(ENTETE_TRAME) &&
       trameReception.endsWith(DELIMITEUR_FIN))
    {
        qDebug() << Q_FUNC_INFO << trameReception;
        decomposerTrame();
        trameReception.clear();
    }
}

/**
 * @brief Méthode d'inititialisation du bluetooth
 */
void Communication::initialiser()
{
    // vérifie la présence du Bluetooth
    if(estBluetoothPresent())
    {
        // active le bluetooth
        peripheriqueLocal.powerOn();

        qDebug() << Q_FUNC_INFO << peripheriqueLocal.name()
                 << peripheriqueLocal.address().toString();

        // instancie l'agent de recherche
        discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
        connect(discoveryAgent,
                SIGNAL(finished()),
                this,
                SLOT(terminerRecherche()));
        connect(discoveryAgent,
                SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
                this,
                SLOT(decouvrirPeripherique(QBluetoothDeviceInfo)));
    }
    else
        qDebug() << Q_FUNC_INFO << "Pas de bluetooh !";
}

/**
 * @brief Vérifie la présence du bluetooth
 */
bool Communication::estBluetoothPresent() const
{
    // vérifie la présence du bluetooth
    if(!peripheriqueLocal.isValid())
        return false;
    return true;
}

/**
 * @brief Méthode qui décompose une trame
 */
void Communication::decomposerTrame()
{
    // $basket;P;{NUMERO};{EQUIPE};\r
    /* Exemples :
        Panier n°1 par joueur Rouge
        $basket;P;1;R;\r
        Panier n°4 par joueur Jaune
        $basket;P;4;J;\r
     */
    QStringList champs =
      trameReception.split(DELIMITEUR_CHAMP, QString::KeepEmptyParts);
    qDebug() << Q_FUNC_INFO << champs;
    // "$basket" "P" "4" "J" "\r"
    //  0        1   2   3   4
    if(champs.at(CHAMP_TYPE_TRAME) == TYPE_TRAME_PANIER)
    {
        qDebug() << Q_FUNC_INFO << champs.at(CHAMP_NUMERO_PANIER)
                 << champs.at(CHAMP_COULEUR_EQUIPE);
        emit nouveauPanier(champs.at(CHAMP_NUMERO_PANIER),
                           champs.at(CHAMP_COULEUR_EQUIPE));
    }
}
