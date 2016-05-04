#include "clientthread.h"

ClientThread::ClientThread(qintptr socketDescriptor,QObject *parent)
    : QThread (parent), socketDescriptor_(socketDescriptor)
{

}

void ClientThread::run()
{
    //Crear el objeto QTcpSocket para la conexion
    QTcpSocket tcpSocket;


}


