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
#include <QSqlDatabase>
#include <QSqlQuery>

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

    int get_trasferedData();
    void reset_transferedData();


private slots:

    void readData();
    void disconnection();
    void socketError(QAbstractSocket::SocketError);
    void handshakeComplete();



private:


    QSettings settings;
    Room *room_;
    int transferedData_;
    bool logged;

    void joinRoom(QString name);

};

#endif // CLIENT_H
