#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <QObject>
#include <QTcpServer>
#include <QSettings>
#include <QDir>
#include <QTimer>
#include <QtSql/QtSql>



#include "client.h"
#include "room.h"

class Server: public QTcpServer
{
    Q_OBJECT

public:

    Server(QObject *parent = 0);


private:

    QSettings settings;
    void incomingConnection(qintptr socketDescriptor);
    QTimer *timer_;
    QFile *stadistics_;

private slots:
    void updateStadistics();
};
#endif // SERVER_H
