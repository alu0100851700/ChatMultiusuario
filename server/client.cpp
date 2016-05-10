#include "client.h"

QList<Client*> Client::list;

Client::Client(QTcpSocket *tcpSocket, QObject *parent)
    : QObject(parent), tcpSocket_(tcpSocket)
{
    std::cout << "Client connected" << std::endl;
    connect(tcpSocket_, SIGNAL(readyRead()), this, SLOT(readData()));
}


void Client::readData()
{
    QString text;

    while(tcpSocket_->canReadLine())
        text.append(tcpSocket_->readLine());

    for(int i = 0 ; i < list.length() ; i++ )
        if( list[i] != this )
            list[i]->tcpSocket_->write(text.toLocal8Bit());

}
