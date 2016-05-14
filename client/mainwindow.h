#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QProcess>
#include <QTcpSocket>
#include <QSslSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();

    void on_connectButton_clicked();

    void on_aboutButton_clicked();

    void on_inputTextEdit_returnPressed();

    void on_setupButton_clicked();

    void handleDisconnect();

    void socketError(QAbstractSocket::SocketError);

    void sslErrors(const QList<QSslError> &errors);

public slots:
    void leer_socketservidor();


private:
    Ui::MainWindow *ui;
    bool isConnected_;
    QProcess process_;
    QSslSocket* sslSocket_;
};

#endif // MAINWINDOW_H
