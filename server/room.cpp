#include "room.h"


QList<Room*> Room::list;

Room::Room(QString name):
    name_(name), transferedData_(0)
{
    Room::list.append(this);

    //Crea directorio /home/***/.talkserver
    QDir historyDirectory(QDir::homePath() + "/.talkServer/history");
    if(!historyDirectory.exists())
            historyDirectory.mkdir(QDir::homePath() + "/.talkServer/history");

    history_ = new QFile(QDir::homePath() + "/.talkServer/history" + name_);

}


void Room::join(Client *client){
    bool inList=false;
    for(int i=0; i < clients_.size() ; i++ )
        if( clients_[i] == client)
            inList=true;

    if(!inList) {
        Message message;
        QString username = "Server";
        QString text = "Connected to " + name_.toUpper() + " room";

        message.set_username(username.toUtf8().constData(),
                             username.toUtf8().length());

        message.set_timestamp(QDateTime::currentDateTime().toMSecsSinceEpoch());

        message.set_type(Message::TEXT);

        message.set_data(text.toUtf8().constData(),
                         text.toUtf8().length());

        std::string buffer;
        message.SerializeToString(&buffer);


        client->sslSocket_->write(buffer.c_str(), buffer.size());
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
        if( clients_[i] != client ){
            clients_[i]->sslSocket_->write(data, data.size());
            transferedData_ += data.size();
        }

    Message message;
    message.ParseFromArray(data, data.length());
    std::string username = message.username();
    int timestamp = message.timestamp();
    std::string text = message.data();


    if (!history_->open(QIODevice::Append | QIODevice::Text))
            return;

    QTextStream out(history_);

    out << QString::fromUtf8(username.c_str()) << "\n"
        << QString::number(timestamp) << "\n"
        << QString::fromUtf8(text.c_str()) << "\n";


    history_->close();
}

void Room::sendHistory(Client *client){
    if (!history_->open(QIODevice::ReadWrite | QIODevice::Text))
              return;

    while(!history_->atEnd() ){
        QByteArray line = history_->readLine();
        std::string username =line.toStdString();

        line = history_->readLine();
        int timestamp = line.toInt();

        line = history_->readLine();
        std::string text = line.toStdString();

        username.erase(std::remove(username.begin(), username.end(), '\n'), username.end());
        text.erase(std::remove(text.begin(), text.end(), '\n'), text.end());

        Message message;

        message.set_username(username.c_str(),
                             username.length());

        message.set_timestamp(timestamp);

        message.set_type(Message::TEXT);

        message.set_data(text.c_str(),
                         text.length());

        std::string buffer;
        message.SerializeToString(&buffer);

        client->sslSocket_->write(buffer.c_str(), buffer.size());
        client->sslSocket_->write("\n");

        transferedData_ += buffer.size();

        std::cout << buffer << std::endl;
    }


    history_->close();
}

int Room::get_trasferedData()
{
    return transferedData_;
}

void Room::reset_transferedData()
{
    transferedData_ = 0;
}
