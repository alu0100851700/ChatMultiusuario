#include <QtGlobal>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    isConnected_(false),
    sslSocket_(new QSslSocket (this)),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QSettings settings;
    ui->serverAddress->setText(settings.value("serverAddress","127.0.0.1").toString());
    ui->portBox->setValue(settings.value("port",6000).toInt());

/*/////////////////////////////////////////////////////////////////////////*/
    if (sslSocket_->supportsSsl())
      {
        ui->ConnectButton->setEnabled(true);
        sslSocket_->setProtocol(QSsl::TlsV1_0);
      }
    else{
        QString noSslMsg = QString("%1\n%2")
                .arg("*** Your version of Qt does support SSL ***")
                .arg("If you believe that your "
                     "version of Qt has SSL support enabled, you may "
                     "need to install the OpenSSL run-time libraries.");
        ui->versionMessage->setText(noSslMsg);
        ui->ConnectButton->setEnabled(false);
    }

    connect(sslSocket_,SIGNAL(connected()),this, SLOT(socketConneted()));

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_ConnectButton_clicked()
{

    if(ui->serverAddress->text().isEmpty()){
        QMessageBox::critical(this, "Talk GUI",
                              "Se necesita la direccion del Servidor");
        return;
    }
    else {
        QSettings settings;
        settings.setValue("serverAddress",ui->serverAddress->text());
        settings.setValue("port",ui->portBox->value());
    }


    if(isConnected_){

        sslSocket_->disconnectFromHost();
        ui->ConnectButton->setText("Connect");
        isConnected_=false;

    }
    else{
        QSettings settings;
        QString serverAddress = settings.value("serverAddress",
                                               "127.0.0.1").toString();
        int port = settings.value("port",6000).toInt();
        QString username = settings.value("username").toString();

        connect(sslSocket_, SIGNAL(error(QAbstractSocket::SocketError)),
                        this, SLOT(socketError(QAbstractSocket::SocketError)));
        connect(sslSocket_, SIGNAL(sslErrors(QList<QSslError>)),
                this, SLOT(sslErrors(QList<QSslError>)));

        QList<QSslError> errorsThatCanBeIgnored;

        sslSocket_->connectToHostEncrypted(serverAddress,port);
    }
}

void SettingsDialog::socketError(QAbstractSocket::SocketError)
{
    QMessageBox::critical(this, tr("Connection error"), sslSocket_->errorString());
}

void SettingsDialog::sslErrors(const QList<QSslError> &errors)
{
    sslSocket_->ignoreSslErrors();
}

void SettingsDialog::socketConneted()
{
    ui->ConnectButton->setText("Disconnect");
    isConnected_=true;

    this->accept(); //Hides the modal dialog

    MainWindow z;
    z.initializeSocket(sslSocket_);
    z.exec();


    this->show();   //When login window is close settings appears
}
