#ifndef WEBCAM_H
#define WEBCAM_H

#include <QDialog>

namespace Ui {
class Webcam;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;

class Webcam : public QDialog
{
    Q_OBJECT

public:
    explicit Webcam(QWidget *parent = 0);
    ~Webcam();
private slots:
    void startCamera();
    void stopCamera();
    void captureCamera();

private:
    Ui::Webcam *ui;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;
    QMenu *mOpcionesMenu;
    QAction *mEncenderAction;
    QAction *mApagarAction;
    QAction *mCapturaAction;
};

#endif // WEBCAM_H
