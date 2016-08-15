#include "client.h"
#include <QHostAddress>

QList<Client*> Client::list;

Client::Client(QSslSocket *sslSocket, QObject *parent)
    : QObject(parent), sslSocket_(sslSocket), room_(NULL)
{

    QString key = settings.value("sslkey",QDir::currentPath() + "/certificate/server.key").toString();
    QString crt = settings.value("sslcrt",QDir::currentPath() + "/certificate/server.crt").toString();

    if(sslSocket_->supportsSsl()){
        connect(sslSocket_, SIGNAL(encrypted()), this, SLOT(handshakeComplete()));
        connect(sslSocket_, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(socketError(QAbstractSocket::SocketError)));
        connect(sslSocket_, static_cast<void(QSslSocket::*)(const QList<QSslError> &)>(&QSslSocket::sslErrors),
            [=](const QList<QSslError> &errors){ sslSocket_->ignoreSslErrors(); });

        sslSocket_->setProtocol(QSsl::TlsV1_0);

        sslSocket_->setPrivateKey(key.toUtf8().constData(), QSsl::Rsa);
        sslSocket_->setLocalCertificate(crt.toUtf8().constData());
        sslSocket_->startServerEncryption();


    }

    // PRUEBA SALA ÚNICA
    /*
    bool existsRoom = false;
    QString name = "room1";

    for(int i=0; i < Room::list.size(); i++){

        if( Room::list[i]->name_ == name )
            existsRoom = true;
            room_ = Room::list[i];
        }
     if (!existsRoom)   room_ = new Room(name);

     room_->join(this);
*/
}

void Client::readData()
{

    QString text = QString("[%1] Incomming Data from %2:%3")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss ap"))
            .arg((sslSocket_->peerAddress()).toString())
            .arg(sslSocket_->peerPort());

    std::cout << text.toUtf8().constData() << std::endl;

    Message message;

    QByteArray data;
    while( sslSocket_->bytesAvailable() > 0 ){
        data += sslSocket_->readAll();
    }

    message.ParseFromArray(data,data.length());

    if( message.type() == Message::TEXT ){          //Mensaje de texto

        room_->send(this, data);

    }
    else if( message.type() == Message::AVATAR ){   //Mensaje de avatar
        //Añadir avatar a la base de datos
        for( int i = 0 ; i < list.length() ; i++ )
            if( list[i] != this )
                list[i]->sslSocket_->write(data);
    }
    else if( message.type() == Message::LOGIN  ){   //Mensaje de login
        std::string username = message.username();
        std::string password = message.data();
        //Comprobar si está en la base de datos y coincide
        //Si no está agregarlo
    }
    else if( message.type() == Message::JOINROOM ){ //Mensaje para entrar en sala
        QString name = message.data().c_str();

        std::cout << "JOINROOM" << name.toUtf8().constData() << std::endl;
        //--------- JOIN ROOM ------------
        bool existsRoom = false;
         for(int i=0; i < Room::list.size(); i++){
            std::cout << 1 << std::endl; ////////////////////
           if( Room::list[i]->name_ == name )
               existsRoom = true;
               room_ = Room::list[i];
          }



          if(room_ != NULL){
           room_->leave(this);
          }

          if(!existsRoom ){
           room_ = new Room(name);
           Room::list.append(room_);
          }

          room_->join(this);


    }


}


void Client::disconnection()
{
    QString text = QString("[%1] Close connection from %2:%3")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss ap"))
            .arg((sslSocket_->peerAddress()).toString())
            .arg(sslSocket_->peerPort());

    std::cout << text.toUtf8().constData() << std::endl;
}

void Client::socketError(QAbstractSocket::SocketError)
{
    std::cerr << sslSocket_->errorString().toUtf8().constData() << std::endl;
}

void Client::handshakeComplete()
{
    connect(sslSocket_, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(sslSocket_, SIGNAL(disconnected()), this, SLOT(disconnection()));

    QString text = QString("[%1] Accepted connection from %2:%3")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss ap"))
            .arg((sslSocket_->peerAddress()).toString())
            .arg(sslSocket_->peerPort());

    std::cout << text.toUtf8().constData() << std::endl;

}

