#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <QObject>
#include <QSslSocket>
#include <QList>
#include <QSsl>
#include <QDateTime>


class Client : public QObject
{
    Q_OBJECT

public:

    static QList<Client*> list;

    Client(QSslSocket* sslSocket, QObject *parent);


private slots:

    void readData();
    void disconnection();
    void socketError(QAbstractSocket::SocketError);
    void handshakeComplete();

private:

    QSslSocket *sslSocket_;

};

#endif // CLIENT_H
