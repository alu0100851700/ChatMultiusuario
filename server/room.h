#ifndef ROOM_H
#define ROOM_H

#include "client.h"

#include <iostream>
#include <QSslSocket>
#include <QDir>
#include <QList>
#include <algorithm>

#include "talkmessage.pb.h"

class Client;
class Room
{
public:
    static QList<Room*> list;

    Room(QString name);

    void join(Client *client);
    void leave(Client *client);
    void send(Client *client, QByteArray data);
    QString name_;

    int get_trasferedData();
    void reset_transferedData();

private:

    void    sendHistory(Client *client);
    int     transferedData_;
    QFile   *history_;
    QList<Client*> clients_;
};

#endif // ROOM_H
