#include "webcam.h"
#include "ui_webcam.h"
#include "QCamera"
#include "QCameraViewfinder"
#include "QCameraImageCapture"
#include "QVBoxLayout"
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include<QSettings>

Webcam::Webcam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Webcam)
{
    ui->setupUi(this);
    mCamera = new QCamera(this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraImageCapture = new QCameraImageCapture(mCamera,this);
    mLayout = new QVBoxLayout;

    mLayout->addWidget(mCameraViewfinder);
    ui->scrollArea->setLayout(mLayout);
    mCamera->setViewfinder(mCameraViewfinder);
    mLayout->setMargin(0);
    mCamera->start();


    }


Webcam::~Webcam()
{
    delete ui;
}


void Webcam::on_CapturePushButton_clicked()
{
    mCameraImageCapture->setCaptureDestination(
                QCameraImageCapture::CaptureToFile);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mCamera->searchAndLock();
    QString path;
    if(QDir(QDir::homePath()+"/images").exists())
        path=QDir::homePath()+"/images/profile.jpg";
    else
         path=QDir::homePath()+"/Imágenes/profile.jpg";
    mCameraImageCapture->capture(path);
    mCamera->unlock();
    QSettings settings;
    settings.setValue("rutaAvatar",path);
}
