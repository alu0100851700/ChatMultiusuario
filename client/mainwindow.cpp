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

    connect(&process_,SIGNAL(finished(int,QProcess::ExitStatus)),
            SLOT(processFinished(int,QProcess::ExitStatus)));
    connect(&process_,SIGNAL(readyReadStandardOutput()),
             SLOT(processReadyReadStandardOutput()));
    connect(&process_,SIGNAL(error(QProcess::ProcessError)),
            SLOT(processError(QProcess::ProcessError)));
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
        //TODO: implementar el código para desconectar
        process_.terminate();
    }
    else{
        QSettings settings;
        QString serverAddress = settings.value("serverAddress","127.0.0.1").toString();
        int port = settings.value("port",6000).toInt();
        QString username = settings.value("username").toString();

        //TODO: implementar el código para conectar
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
    process_.write(line.toLocal8Bit());
    ui->inputTextEdit->clear();
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
       ui->connectButton->setText("Connect");
       isConnected_=false;
}

void MainWindow::processReadyReadStandardOutput()
{
    while(process_.canReadLine()){
        QString line=process_.readLine();
        line.truncate(line.length()-1);
        ui->outputTextEdit->appendPlainText(line);
    }
}

void MainWindow::processError(QProcess::ProcessError error)
{
    QMessageBox::critical(this,"Talk GUI",
                          "Error con Talk.\n" + process_.errorString());
}

void MainWindow::on_setupButton_clicked()
{
    SettingsDialog dialog;
    dialog.exec();
}

void MainWindow::on_Escribiralservidor_clicked()
{

    //tcpSocket_->write(&dataIn);

}

void MainWindow ::leer_socketservidor()
{
     QByteArray dataIn=tcpSocket_->readLine();

}
