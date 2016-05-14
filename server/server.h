#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <QObject>
#include <QTcpServer>
#include <QSettings>


#include "client.h"

class Server: public QTcpServer
{
    Q_OBJECT

public:

    Server(QObject *parent = 0);


private:

    QSettings settings;
    void incomingConnection(qintptr socketDescriptor);

};
#endif // SERVER_H
