#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    //Recuperar configuración
    int listenPort = settings.value("port",6000).toInt(); //Por defecto 6000

    std::cout << "Puerto: " << listenPort << std::endl;

    listen(QHostAddress::Any, listenPort);

    connect(this, SIGNAL( newConnection() ), SLOT( sessionOpened() ) );

}


void Server::sessionOpened()
{
    while(hasPendingConnections()) {
        //clientConnection->write(data);
        Client::list.append(
                  new Client(nextPendingConnection(), this));
    }
}

