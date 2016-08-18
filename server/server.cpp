#include "server.h"


Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    //Recuperar configuración
    int listenPort = settings.value("port",6000).toInt(); //Por defecto 6000

    std::cout << QString("Server listenting for connections on %1\n").arg(listenPort).toUtf8().constData() << std::endl;

    listen(QHostAddress::Any, listenPort);


    //Crea directorio /home/***/.talkserver
    QDir historyDirectory(QDir::homePath() + "/.talkServer");
    if(!historyDirectory.exists())
            historyDirectory.mkdir(QDir::homePath() + "/.talkServer");

    history_ = new QFile(QDir::homePath() + "/.talkServer/history");
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QSslSocket *sslSocket = new QSslSocket;
    if (sslSocket->setSocketDescriptor(socketDescriptor)) {
        Client *newClient = new Client(sslSocket, history_, this);
        Client::list.append(newClient);
    } else {
        delete sslSocket;
    }
}
