#include <QMessageBox>
#include <aboutdialog.h>
#include <settingsdialog.h>
#include <QSettings>
#include <QTcpSocket>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    isConnected_(false),
    process_(this),
    sslSocket_(new QSslSocket(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    if (sslSocket_->supportsSsl())
      {
        ui->connectButton->setEnabled(true);
        sslSocket_->setProtocol(QSsl::TlsV1_0);
        ui->outputTextEdit->appendPlainText("SslSupport");
      }
    else{
        QString noSslMsg = QString("%1\n%2")
                .arg("*** Your version of Qt does support SSL ***")
                .arg("If you believe that your "
                     "version of Qt has SSL support enabled, you may "
                     "need to install the OpenSSL run-time libraries.");
        ui->outputTextEdit->appendPlainText(noSslMsg);
        ui->connectButton->setEnabled(false);
    }

    connect(sslSocket_,SIGNAL(disconnected()),this,SLOT(handleDisconnect()));
    connect(sslSocket_,SIGNAL (readyRead()),this, SLOT(leer_socketservidor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_connectButton_clicked()
{
    if(isConnected_){

        sslSocket_->disconnectFromHost();
        ui->connectButton->setText("Connect");
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
        //errorsThatCanBeIgnored

        sslSocket_->connectToHostEncrypted(serverAddress,port);

        ui->connectButton->setText("Disconnect");
        isConnected_=true;
    }
}

void MainWindow::on_aboutButton_clicked()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_inputTextEdit_returnPressed()
{
    QString line= ui->inputTextEdit->text();
    ui->outputTextEdit->appendPlainText(line);
    line += '\n';

    sslSocket_->write(line.toLocal8Bit().constData());
    ui->inputTextEdit->clear();


}

void MainWindow::on_setupButton_clicked()
{
    SettingsDialog dialog;
    dialog.exec();
}

void MainWindow::handleDisconnect()
{
    ui->connectButton->setText("Connect");
    isConnected_=false;
}


void MainWindow ::leer_socketservidor()
{
     while(sslSocket_->canReadLine()){
         QByteArray dataIn=sslSocket_->readLine();
         ui->outputTextEdit->appendPlainText(QString (dataIn));
     }

}

void MainWindow::socketError(QAbstractSocket::SocketError)
{
    QMessageBox::critical(this, tr("Connection error"), sslSocket_->errorString());
}

void MainWindow::sslErrors(const QList<QSslError> &errors)
{
    sslSocket_->ignoreSslErrors();
}
