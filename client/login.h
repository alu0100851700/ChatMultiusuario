#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSslSocket>
#include "talkmessage.pb.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void initializeSocket(QSslSocket *sslSocket);
    void ver_estadoLogin();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
    QSslSocket *sslSocket_;
    bool estadoLogin;
};

#endif // LOGIN_H
