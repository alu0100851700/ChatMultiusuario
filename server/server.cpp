#include "server.h"

#define INTERVALTIMER 10    //in sec
Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    // Restore configuration
    int listenPort = settings.value("port",6000).toInt(); // Default: 6000

    std::cout << QString("Server listenting for connections on %1\n").arg(listenPort).toUtf8().constData() << std::endl;

    listen(QHostAddress::Any, listenPort);




    /*************************** DATABASE *******************************/
    // Create database
    QString dbpath = "login.sqlite";
    QSqlDatabase login_db =  QSqlDatabase::addDatabase("QSQLITE");
    login_db.setDatabaseName(dbpath);

    if(!login_db.open())
        qDebug() << "Failed to open database...";
    else
        qDebug()<< "Conected to login database";

    QSqlQuery query(login_db);

    // Create login table

    query.exec("CREATE TABLE LOGIN_TB(                      "
               "    USERNAME    VARCHAR(20) PRIMARY KEY,    "
               "    PASSWORD    VARCHAR(20));               ");


    login_db.close();
    /*******************************************************************/

    // Stadistics file
    QDir serverDirectory(QDir::homePath() + "/.talkServer/log");

    if(!serverDirectory.exists())
            QDir().mkdir(QDir::homePath() + "/.talkServer/log");

    stadistics_ = new QFile(QDir::homePath() + "/.talkServer/log/stadistic.log");

    // Stadistics timer
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

    /******************* INCOMING BITS **********************/
    int inTransferedData=0;
    for(int i=0; i<Client::list.length(); i++){
        inTransferedData += Client::list[i]->get_trasferedData();
        Client::list[i]->reset_transferedData();
    }

    int inbps = (inTransferedData*8)/INTERVALTIMER;
    /*******************************************************/


    /***************** OUTGOING BITS **********************/
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
