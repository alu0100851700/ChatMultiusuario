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


private slots:

    void sessionOpened();

};
#endif // SERVER_H
