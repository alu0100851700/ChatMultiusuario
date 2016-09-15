#include "client.h"
#include <QHostAddress>

QList<Client*> Client::list;

Client::Client(QSslSocket *sslSocket, QObject *parent)
    : QObject(parent),
      sslSocket_(sslSocket),
      room_(NULL),
      transferedData_(0),
      logged(false)
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
}

int Client::get_trasferedData()
{
    return transferedData_;
}

void Client::reset_transferedData()
{
    transferedData_ = 0;
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

    transferedData_ += data.length();

    message.ParseFromArray(data,data.length());

    if( message.type() == Message::TEXT ){          //Mensaje de texto

        room_->send(this, data);

    }
    else if( message.type() == Message::AVATAR ){   //Mensaje de avatar
        //Añadir avatar a la base de datos
        /*
        for( int i = 0 ; i < list.length() ; i++ )
            if( list[i] != this )
                list[i]->sslSocket_->write(data);
                */
    }
    else if( message.type() == Message::LOGIN  ){   //Mensaje de login
        QString username = QString::fromStdString(message.username());
        QString password = QString::fromStdString(message.data());
        //Comprobar si está en la base de datos y coincide
        //Si no está agregarlo

        /*************************** DATABASE *******************************/
        // Create database
        QString dbpath = "login.sqlite";
        QSqlDatabase login_db = QSqlDatabase::addDatabase("QSQLITE");
        login_db.setDatabaseName(dbpath);

        if(!login_db.open())
            qDebug() << "Failed to open database...";
        else
            qDebug()<< "Conected to login database";

        QSqlQuery query(login_db);


        query.exec("SELECT PASSWORD                     "
                   "FROM LOGIN_TB                       "
                   "WHERE USERNAME = '" + username + "';");
        query.next();

        if(!query.next()){   // User does not exists
            query.exec("INSERT INTO LOGIN_TB            "
                       "VALUES('" + username + "', '" + password +"');    ");

            query.exec("SELECT PASSWORD                     "
                       "FROM LOGIN_TB                       "
                       "WHERE USERNAME = '" + username + "';");
            query.next();
        }

        QString dbpassword = query.value(0).toString();

        QString text;

        if(password == dbpassword){
            logged = true;
            qDebug() << username.toUpper() + " logged in";
            text = "1";
        }
        else{
            qDebug() << username.toUpper() + " failed while logging";
            text = "0";
        }


        login_db.close();
        /*******************************************************************/



        /**************************** MESSAGE ******************************/
        Message message;
        QString S_username = "Server";

        message.set_username(S_username.toUtf8().constData(),
                             S_username.toUtf8().length());

        message.set_timestamp(QDateTime::currentDateTime().toMSecsSinceEpoch());

        message.set_type(Message::TEXT);

        message.set_data(text.toUtf8().constData(),
                         text.toUtf8().length());

        std::string buffer;
        message.SerializeToString(&buffer);

        sslSocket_->write(buffer.c_str(), buffer.size());


        /*******************************************************************/
    }
    else if( message.type() == Message::JOINROOM ){ //Mensaje para entrar en sala
        QString name = message.data().c_str();
        joinRoom(name);
    }


}


void Client::disconnection()
{
    QString text = QString("[%1] Close connection from %2:%3")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss ap"))
            .arg((sslSocket_->peerAddress()).toString())
            .arg(sslSocket_->peerPort());

    std::cout << text.toUtf8().constData() << std::endl;

    for(int i=0; i<Client::list.length(); i++)
        if(Client::list[i] == this)
            Client::list.removeAt(i);
    delete this;
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

void Client::joinRoom(QString name)
{
    qDebug() << "Join room: " << name;
    if(logged){
        if(room_ != NULL){
            room_->leave(this);
        }

        bool existsRoom = false;
        for(int i=0; i < Room::list.length(); i++){
            if( Room::list[i]->name_ == name )
                existsRoom = true;
                room_ = Room::list[i];
        }

        if(!existsRoom )    room_ = new Room(name);


        room_->join(this);
    }
    else{
        Message message;
        QString text = "Log in to change room";
        QString username = "Server";

        message.set_username(username.toUtf8().constData(),
                             username.toUtf8().length());

        message.set_timestamp(QDateTime::currentDateTime().toMSecsSinceEpoch());

        message.set_type(Message::TEXT);

        message.set_data(text.toUtf8().constData(),
                         text.toUtf8().length());

        std::string buffer;
        message.SerializeToString(&buffer);

        sslSocket_->write(buffer.c_str(), buffer.size());
    }
}

