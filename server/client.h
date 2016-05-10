#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <QObject>
#include <QSslSocket>
#include <QList>


class Client : public QObject
{
    Q_OBJECT

public:

    static QList<Client*> list;

    Client(QTcpSocket* tcpSocket, QObject *parent);


private slots:

    void readData();


private:

    QTcpSocket *tcpSocket_;

};

#endif // CLIENT_H
