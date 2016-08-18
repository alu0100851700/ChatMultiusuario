#include <QMessageBox>
#include "roomdialog.h"
#include "ui_roomdialog.h"

RoomDialog::RoomDialog(QWidget *parent) :
    QDialog(parent),
    sslSocket_(NULL),
    ui(new Ui::RoomDialog)
{
    ui->setupUi(this);
}

RoomDialog::~RoomDialog()
{
    delete ui;
}

void RoomDialog::on_buttonBox_accepted()
{

    QString line=ui->roomLineEdit->text() ;
    QSettings settings;

    QString username = settings.value("username").toString();

    Message message;
    message.set_username(username.toUtf8().constData(),
                         username.toUtf8().length());
    message.set_timestamp(0);
    message.set_type(Message::JOINROOM);
    message.set_data(line.toUtf8().constData(),
                     line.toUtf8().length());

    std::string buffer;
    message.SerializeToString(&buffer);

    sslSocket_->write(buffer.c_str(), buffer.size());
}

 void RoomDialog::initializeSocket(QSslSocket* sslSocket){
     sslSocket_=sslSocket;
 }
