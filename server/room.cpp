#include "room.h"


QList<Room*> Room::list;

Room::Room(QString name):
    name_(name)
{
    Room::list.append(this);

    //Crea directorio /home/***/.talkserver
    QDir historyDirectory(QDir::homePath() + "/.talkServer");
    if(!historyDirectory.exists())
            historyDirectory.mkdir(QDir::homePath() + "/.talkServer");

    history_ = new QFile(QDir::homePath() + "/.talkServer/" + name_);

    list.append(this);
}


void Room::join(Client *client){
    bool inList=false;
    for(int i=0; i < clients_.size() ; i++ )
        if( clients_[i] == client)
            inList=true;

    if(!inList) {
        clients_.append(client);
        sendHistory(client);
    }
}

void Room::leave(Client *client){
    for(int i=0; i < clients_.size() ; i++ )
        if( clients_[i] == client )
            clients_.removeAt(i);
}

void Room::send(Client *client, QByteArray data){
    std::cout << "Dentro de send" << std::endl;

    for(int i=0; i < clients_.size() ; i++ )
        if( clients_[i] != client )
            clients_[i]->sslSocket_->write(data, data.size());


    if (!history_->open(QIODevice::Append | QIODevice::Text))
            return;

    QTextStream out(history_);

    out << data;

    history_->close();
}

void Room::sendHistory(Client *client){
    if (!history_->open(QIODevice::ReadOnly | QIODevice::Text))
              return;

    while(!history_->atEnd()){
        QByteArray line = history_->readLine();
        std::cout << "msj: " << line.toStdString();
        client->sslSocket_->write(line.constData(), line.length());


    }


    history_->close();
}
