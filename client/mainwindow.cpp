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
    tcpSocket_(new QTcpSocket(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Conectamos la señal de "leer" con el slot

    connect(tcpSocket_,SIGNAL (readyRead()),this,
            SLOT(leer_socketservidor()));

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

        tcpSocket_->disconnectFromHost();
        ui->connectButton->setText("Connect");
        isConnected_=false;

    }
    else{
        QSettings settings;
        QString serverAddress = settings.value("serverAddress","127.0.0.1").toString();
        int port = settings.value("port",6000).toInt();
        QString username = settings.value("username").toString();

        tcpSocket_->connectToHost(serverAddress,port);

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
    QString line= ui->inputTextEdit->text() +'\n';

    tcpSocket_->write(line.toLocal8Bit());
    ui->inputTextEdit->clear();

}

void MainWindow::on_setupButton_clicked()
{
    SettingsDialog dialog;
    dialog.exec();
}


void MainWindow ::leer_socketservidor()
{
     while(tcpSocket_->canReadLine()){
         QByteArray dataIn=tcpSocket_->readLine();
         ui->outputTextEdit->appendPlainText(QString (dataIn));
     }

}
