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


#include "talkmessage.pb.h"

class Client : public QObject
{
    Q_OBJECT

public:

    static QList<Client*> list;

    Client(QSslSocket* sslSocket, QFile* history, QObject *parent);


private slots:

    void readData();
    void disconnection();
    void socketError(QAbstractSocket::SocketError);
    void handshakeComplete();

private:

    void sendHistory();

    QSslSocket *sslSocket_;
    QSettings settings;
    QFile *history_;

};

#endif // CLIENT_H
