#include "client.h"
#include <QHostAddress>

QList<Client*> Client::list;

Client::Client(QSslSocket *sslSocket, QFile* history, QObject *parent)
    : QObject(parent), sslSocket_(sslSocket), history_(history)
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
        for( int i = 0 ; i < list.length() ; i++ )
            if( list[i] != this )
                list[i]->sslSocket_->write(data);

        history_->open(QIODevice::Append);
        history_->write(data, data.length());
        history_->close();
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
        std::string room = message.data();
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

    sendHistory();
}

void Client::sendHistory()
{
    if (!history_->open(QIODevice::ReadOnly | QFile::Text))
              return;

    while(!history_->atEnd()){
        QByteArray line = history_->readLine();

        sslSocket_->write(line, line.length());

        std::cout << "ll: " << line.length() << " " << line.toStdString() << std::endl;
    }


    history_->close();

}
