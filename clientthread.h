#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>

class ClientThread : public QThread
{
    Q_OBJECT
public:
    ClientThread(qintptr socketDescriptor,QObject *parent);
    void run();
signals:
    void error(QTcpSocket::SocketError socketError);
private:
    qintptr socketDescriptor_;
};

#endif // CLIENTTHREAD_H
