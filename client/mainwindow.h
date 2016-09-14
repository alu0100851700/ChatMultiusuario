#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QProcess>
#include <QTcpSocket>
#include <QSslSocket>
#include <QCamera>
#include <QMenu>
#include <QAction>
#include <QDateTime>
#include <login.h>


#include "talkmessage.pb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initializeSocket(QSslSocket *sslSocket);

private slots:
    void on_exitButton_clicked();

    void on_aboutButton_clicked();

    void on_inputTextEdit_returnPressed();

    void on_setupButton_clicked();

    void socketError(QAbstractSocket::SocketError);

    void sslErrors(const QList<QSslError> &errors);

    void on_roomButton_clicked();

public slots:
    void leer_socketservidor();
    void webcamOptions();
    void cargarImagenOptions();


private:
    Ui::MainWindow *ui;
    QSslSocket* sslSocket_;
    QMenu *mAvatarMenu;
    QAction *mWebcamAction;
    QAction *mCargarAction;
    Login lg;
};

#endif // MAINWINDOW_H
