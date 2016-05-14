#include "client.h"
#include <QHostAddress>

QList<Client*> Client::list;

Client::Client(QSslSocket *sslSocket, QObject *parent)
    : QObject(parent), sslSocket_(sslSocket)
{


    if(sslSocket_->supportsSsl()){
        connect(sslSocket_, SIGNAL(encrypted()), this, SLOT(handshakeComplete()));
        connect(sslSocket_, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(socketError(QAbstractSocket::SocketError)));
        connect(sslSocket_, static_cast<void(QSslSocket::*)(const QList<QSslError> &)>(&QSslSocket::sslErrors),
            [=](const QList<QSslError> &errors){ sslSocket_->ignoreSslErrors(); });

        sslSocket_->setProtocol(QSsl::TlsV1_0);

        sslSocket_->setPrivateKey("/home/david/Documentos/Sistemas_Operativos_Avanzados/ChatMultiusuario/server/certificate/server.key", QSsl::Rsa);
        sslSocket_->setLocalCertificate("/home/david/Documentos/Sistemas_Operativos_Avanzados/ChatMultiusuario/server/certificate/server.crt");
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

    QByteArray data;
    while(sslSocket_->canReadLine()){
        data += sslSocket_->readLine();
    }


    for(int i = 0 ; i < list.length() ; i++ )
        if( list[i] != this )
            list[i]->sslSocket_->write(data);

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
