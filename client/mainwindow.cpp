#include <QMessageBox>
#include <aboutdialog.h>
#include <settingsdialog.h>
#include <webcam.h>
#include <QSettings>
#include <QTcpSocket>
#include <QFileDialog>
#include <QPixmap>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    isConnected_(false),
    sslSocket_(new QSslSocket(this)),
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
    //ui->Avatar->setLayout();

    /*//////////////////////////////*/
    if (sslSocket_->supportsSsl())
      {
        ui->connectButton->setEnabled(true);
        sslSocket_->setProtocol(QSsl::TlsV1_0);
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

    //sslSocket_->write(line.toLocal8Bit().constData());
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

void MainWindow::handleDisconnect()
{
    ui->connectButton->setText("Connect");
    isConnected_=false;
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
        ui->outputTextEdit->appendPlainText(QString::fromUtf8(text.c_str()));
    }

}

void MainWindow::webcamOptions()
{
    Webcam cam;
    cam.exec();
}

void MainWindow::cargarImagenOptions()
{
    QString filename = QFileDialog::getOpenFileName(this,"Foto",QDir::homePath(),
                                                    "Imagen (*.jpg,*.jpeg)");
    QSettings settings;
    settings.setValue("rutaAvatar",filename);
    QPixmap imagen;
    imagen.load(filename);
    QIcon ButtonIcon(imagen);
    ui->Avatar->setIcon(ButtonIcon);
    ui->Avatar->setIconSize(QSize(100,100));

}

void MainWindow::socketError(QAbstractSocket::SocketError)
{
    QMessageBox::critical(this, tr("Connection error"), sslSocket_->errorString());
}

void MainWindow::sslErrors(const QList<QSslError> &errors)
{
    sslSocket_->ignoreSslErrors();
}

