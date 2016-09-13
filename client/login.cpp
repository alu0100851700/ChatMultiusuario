#include "login.h"
#include "roomdialog.h"
#include "ui_login.h"
#include <QDebug>
#include <QSqlError>
Login::Login(QWidget *parent) :
    QDialog(parent),
    estadoLogin(1),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QSettings settings;



    QString username = settings.value("username").toString();

    if( username.isNull() || username.isEmpty())
        username= getenv("USER");

    ui->lineEdit_username->setText(username);

}

Login::~Login()
{
    delete ui;
}

void Login::initializeSocket(QSslSocket *sslSocket)
{
    sslSocket_=sslSocket;
    connect(sslSocket_,SIGNAL(readyRead()),this, SLOT(ver_estadoLogin()));
}

void Login::on_pushButton_login_clicked()
{

    QSettings settings;


    QString username = ui->lineEdit_username->text();

    if(username.isEmpty())
        return;

    settings.setValue("username",username);

    QString password = ui->lineEdit_password->text();

    Message message;
    message.set_username(username.toUtf8().constData(),
                         username.toUtf8().length());
    QDateTime timestamp;
    message.set_timestamp(timestamp.toTime_t());
    message.set_type(Message::LOGIN);
    message.set_data(password.toUtf8().constData(),
                     password.toUtf8().length());

    std::string buffer;
    message.SerializeToString(&buffer);

    sslSocket_->write(buffer.c_str(), buffer.size());

    if(estadoLogin){
        this->accept(); //Hides the modal dialog

        MainWindow mw;
        mw.initializeSocket(sslSocket_);
        mw.exec();

        this->show();   //When login window is close settings appears
    }
}

void Login::ver_estadoLogin()
{
    Message message;
    QByteArray data;


    data += sslSocket_->readLine();

    message.ParseFromArray(data,data.length());

    std::string username = message.username();

    if( message.type() == Message::TEXT ){  //Mensaje de texto
        std::string text = message.data();

        if((username == "Server") && text == "0"){
            estadoLogin=0;
            QString fallo="Login Fail";
            ui->messageText->appendPlainText(fallo);
        }
    }
}
