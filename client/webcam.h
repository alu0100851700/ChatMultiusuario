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
    void on_CapturePushButton_clicked();

private:
    Ui::Webcam *ui;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *mLayout;

};

#endif // WEBCAM_H
