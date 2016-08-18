#include <QMessageBox>
#include "roomdialog.h"
#include "ui_roomdialog.h"

RoomDialog::RoomDialog(QWidget *parent) :
    QDialog(parent),
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
    QSslSocket *sslSocket=new QSslSocket;
    QString line=ui->roomLineEdit->text() ;

    Message message;
    message.set_timestamp(0);
    message.set_type(Message::JOINROOM);
    message.set_data(line.toUtf8().constData(),
                     line.toUtf8().length());

    std::string buffer;
    message.SerializeToString(&buffer);

    sslSocket->write(buffer.c_str(), buffer.size());
}
