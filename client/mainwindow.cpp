#include <QMessageBox>
#include "roomdialog.h"
#include <aboutdialog.h>
#include <settingsdialog.h>
#include <webcam.h>
#include <QSettings>
#include <QTcpSocket>
#include <QFileDialog>
#include <QPixmap>
#include <login.h>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings settings;

    /*//////OPCIONES DE AVATAR//////*/
    mAvatarMenu = new QMenu("Avatar",this);
    mWebcamAction = new QAction("Webcam",this);
    mCargarAction = new QAction("CargarFichero",this);
    mAvatarMenu->addAction(mWebcamAction);
    mAvatarMenu->addAction(mCargarAction);

    ui->Avatar->setMenu(mAvatarMenu);
    connect(mWebcamAction, SIGNAL(triggered()), this, SLOT(webcamOptions()));
    connect(mCargarAction, SIGNAL(triggered()), this,
            SLOT(cargarImagenOptions()));


    QString filename =
            settings.value("rutaAvatar",QCoreApplication::applicationDirPath()+
                           "/default.jpg").toString();
    QPixmap imagen;
    imagen.load(filename);
    QIcon ButtonIcon(imagen);
    ui->Avatar->setIcon(ButtonIcon);
    ui->Avatar->setIconSize(QSize(100,100));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    qApp->quit();
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

    ui->inputTextEdit->clear();

    Message message;
    QSettings settings;
    QString username = settings.value("username").toString();

    message.set_username(username.toUtf8().constData(),
                         username.toUtf8().length());

    message.set_timestamp(0);

    message.set_type(Message::TEXT);

    message.set_data(line.toUtf8().constData(),
                     line.toUtf8().length());

    std::string buffer;
    message.SerializeToString(&buffer);

    sslSocket_->write(buffer.c_str(), buffer.size());

}

void MainWindow::on_setupButton_clicked()
{
    SettingsDialog dialog;
    dialog.exec();
}

void MainWindow ::leer_socketservidor()
{
    Message message;
    QByteArray data;

    while ( sslSocket_->bytesAvailable() > 0 )
        data += sslSocket_->readAll();

    message.ParseFromArray(data, data.length());

    std::string username = message.username();
    int timestamp = message.timestamp();

    if( message.type() == Message::TEXT ){  //Mensaje de texto
        std::string text = message.data();
        std::string all=username+":"+text;
        ui->outputTextEdit->appendPlainText(QString::fromUtf8(all.c_str()));
        /*ui->outputTextEdit->appendPlainText(QString::fromUtf8(username.c_str()));
        ui->outputTextEdit->appendPlainText(QString::number(timestamp));*/

        if((username == "Server") && text == "0"){

        }

    }
}

void MainWindow::webcamOptions()
{
    Webcam cam;
    cam.exec();
    QSettings settings;
    QString filename =
            settings.value("rutaAvatar",QCoreApplication::applicationDirPath()+
                           "/default.jpg").toString();
    QPixmap imagen;
    imagen.load(filename);
    QIcon ButtonIcon(imagen);
    ui->Avatar->setIcon(ButtonIcon);
    ui->Avatar->setIconSize(QSize(100,100));
}

void MainWindow::cargarImagenOptions()
{
    QString filename = QFileDialog::getOpenFileName(this,"Foto",QDir::homePath(),
                                                    "Imagen (*.jpg *.jpeg)");
    if(!filename.isEmpty()){
        QSettings settings;
        settings.setValue("rutaAvatar",filename);
        QPixmap imagen;
        imagen.load(filename);
        QIcon ButtonIcon(imagen);
        ui->Avatar->setIcon(ButtonIcon);
        ui->Avatar->setIconSize(QSize(100,100));
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


void MainWindow::initializeSocket(QSslSocket* sslSocket)
{
    sslSocket_=sslSocket;
    connect(sslSocket_,SIGNAL(readyRead()),this, SLOT(leer_socketservidor()));
}

void MainWindow::on_roomButton_clicked()
{

    RoomDialog di;
    di.initializeSocket(sslSocket_);
    di.exec();
    ui->outputTextEdit->clear();

    /*
    Login lo;
    lo.exec();
    */
}

void MainWindow::on_exitRoomButton_clicked()
{
    QString roomname="default";
    QSettings settings;

    QString username = settings.value("username").toString();

    Message message;
    message.set_username(username.toUtf8().constData(),
                         username.toUtf8().length());
    QDateTime timestamp;
    message.set_timestamp(timestamp.toTime_t());
    message.set_type(Message::JOINROOM);
    message.set_data(roomname.toUtf8().constData(),
                     roomname.toUtf8().length());

    std::string buffer;
    message.SerializeToString(&buffer);

    sslSocket_->write(buffer.c_str(),buffer.size());

}
