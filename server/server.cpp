#include "server.h"

#define INTERVALTIMER 10    //in sec
Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    //Recuperar configuración
    int listenPort = settings.value("port",6000).toInt(); //Por defecto 6000

    std::cout << QString("Server listenting for connections on %1\n").arg(listenPort).toUtf8().constData() << std::endl;

    listen(QHostAddress::Any, listenPort);


    QDir serverDirectory(QDir::homePath() + "/.talkServer/log");
    if(!serverDirectory.exists())
            serverDirectory.mkdir(QDir::homePath() + "/.talkServer/log");

    stadistics_ = new QFile(QDir::homePath() + "/.talkServer/log/stadistic.log");

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateStadistics()));

    timer_->start(INTERVALTIMER * 1000);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QSslSocket *sslSocket = new QSslSocket;
    if (sslSocket->setSocketDescriptor(socketDescriptor)) {
        Client *newClient = new Client(sslSocket, this);
        Client::list.append(newClient);
    } else {
        delete sslSocket;
    }
}

void Server::updateStadistics()
{
    int clientConnections = Client::list.length();
    int roomsUsed = Room::list.length();

    if (!stadistics_->open(QIODevice::Append | QIODevice::Text))
            return;

    /************* CALCULO LLEGADA BITS ********************/
    int inTransferedData=0;
    for(int i=0; i<Client::list.length(); i++){
        inTransferedData += Client::list[i]->get_trasferedData();
        Client::list[i]->reset_transferedData();
    }

    int inbps = (inTransferedData*8)/INTERVALTIMER;
    /*******************************************************/


    /************* CALCULO SALIDA BITS ********************/
    int outTransferedData=0;
    for(int i=0; i<Room::list.length(); i++){
        outTransferedData += Room::list[i]->get_trasferedData();
        Room::list[i]->reset_transferedData();
    }

    int outbps = (outTransferedData*8)/INTERVALTIMER;
    /*******************************************************/


    QString text;
    text += "\n\n" + QTime::currentTime().toString("HH:mm:ss t");
    text += "\nClient connections: " + QString::number(clientConnections);
    text += "\nRooms Used: " + QString::number(roomsUsed);
    text += "\nbps (Incoming): " + QString::number(inbps);
    text += "\nbps (Outgoing): " + QString::number(outbps);

    std::cout << text.toStdString() << std::endl;
    stadistics_->write(text.toLocal8Bit());

    stadistics_->close();
}
