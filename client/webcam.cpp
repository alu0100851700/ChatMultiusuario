#include "webcam.h"
#include "ui_webcam.h"
#include "QCamera"
#include "QCameraViewfinder"
#include "QCameraImageCapture"
#include "QVBoxLayout"
#include <QMenu>
#include <QAction>
#include <QFileDialog>

Webcam::Webcam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Webcam)
{
    ui->setupUi(this);
    mCamera = new QCamera(this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera,this);
    mLayout = new QVBoxLayout;
    mOpcionesMenu = new QMenu("Opciones",this);
    mEncenderAction = new QAction("Encender",this);
    mApagarAction = new QAction("Apagar",this);
    mCapturaAction = new QAction("Capturar",this);

    mOpcionesMenu->addAction(mEncenderAction);
    mOpcionesMenu->addAction(mApagarAction);
    mOpcionesMenu->addAction(mCapturaAction);

    ui->OpcionesPushButton->setMenu(mOpcionesMenu);
    mCamera->setViewfinder(mCameraViewfinder);
    mLayout->addWidget(mCameraViewfinder);
    mLayout->setMargin(0);
    ui->scrollArea->setLayout(mLayout);



        connect(mEncenderAction, SIGNAL(triggered()), this, SLOT(startCamera()));
        connect(mApagarAction, SIGNAL(triggered()), this, SLOT(stopCamera()));
        connect(mCapturaAction,SIGNAL(triggered()), this, SLOT(captureCamera()));

    }


Webcam::~Webcam()
{
    delete ui;
}

void Webcam::startCamera()
{
    mCamera->start();
}

void Webcam::stopCamera()
{
    mCamera->stop();
}

void Webcam::captureCamera()
{
    QString filename = QFileDialog::getSaveFileName(this,"Capturar","/",
                                                    "Imagen (*.jpg,*.jpeg)");

    if(filename.isEmpty())
        return;

    mCameraImageCapture->setCaptureDestination(
                QCameraImageCapture::CaptureToFile);
    QImageEncoderSettings imageEncoderSettings;
    imageEncoderSettings.setCodec("image/jpeg");
    imageEncoderSettings.setResolution(1600,1200);
    mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mCamera->searchAndLock();
    mCameraImageCapture->capture(filename);
    mCamera->unlock();
}


