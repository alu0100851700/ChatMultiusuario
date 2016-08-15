#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <QObject>
#include <QSslSocket>
#include <QList>
#include <QSsl>
#include <QDateTime>
#include <QSettings>
#include <QDir>

#include "room.h"
#include "talkmessage.pb.h"

class Room;

class Client : public QObject
{
    Q_OBJECT

public:

    static QList<Client*> list;

    Client(QSslSocket* sslSocket, QObject *parent);

    QSslSocket *sslSocket_;


private slots:

    void readData();
    void disconnection();
    void socketError(QAbstractSocket::SocketError);
    void handshakeComplete();



private:


    QSettings settings;
    Room *room_;

};

#endif // CLIENT_H
