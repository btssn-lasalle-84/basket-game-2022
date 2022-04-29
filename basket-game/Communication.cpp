#include "Communication.h"
#include <QString>

Communication::Communication()
{
}

Communication::~Communication()
{
    arreter();
    peripheriqueLocal.setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    qDebug() << Q_FUNC_INFO;
}

void Communication::demarrer()
{
    if(!serveur)
    {
        serveur =
          new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouveauClient()));

        QBluetoothUuid uuid = QBluetoothUuid(serviceUuid);
        serviceInfo         = serveur->listen(uuid, serviceNom);
    }
}

void Communication::arreter()
{
    if(!serveur)
        return;

    serviceInfo.unregisterService();

    if(socket)
    {
        if(socket->isOpen())
            socket->close();
        delete socket;
        socket = NULL;
    }

    delete serveur;
    serveur = NULL;
}

void Communication::nouveauClient()
{
    // on récupère la socket
    socket = serveur->nextPendingConnection();
    if(!socket)
        return;

    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
    connect(socket,
            SIGNAL(error(QBluetoothSocket::SocketError)),
            this,
            SLOT(socketError(QBluetoothSocket::SocketError)));
    connect(socket,
            SIGNAL(stateChanged(QBluetoothSocket::SocketState)),
            this,
            SLOT(socketStateChanged(QBluetoothSocket::SocketState)));
}

void Communication::decomposerTrame()
{
}

bool Communication::trameEstValide()
{
}
