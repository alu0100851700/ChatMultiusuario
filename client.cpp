#include "client.h"

/*Client::Client(QTcpSocket* tcpSocket, QObject *parent)
    : QObject (parent), tcpSocket_ (tcpSocket)
{
    tcpSocket_=new QTcpSocket(this);
    //Conectamos la señal de "leer" con el slot
    tcpSocket_->connectToHost(QHostAddress::LocalHost,8000);
    connect(tcpSocket_,SIGNAL (readyRead()),this,
            SLOT(on_Escribiralservidor_clicked());
}

void Client::on_Escribiralservidor_clicked()
{

    tcpSocket_->write(&dataIn);

}

void Client::leer_socketservidor()
{
     QByteArray dataIn=tcpSocket_->readLine();

}*/
