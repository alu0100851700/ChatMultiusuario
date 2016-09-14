#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSslSocket>
#include "mainwindow.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
private slots:
   void on_ConnectButton_clicked();
   void socketError(QAbstractSocket::SocketError);
   void sslErrors(const QList<QSslError> &errors);

public slots:
   void socketConneted();

private:
    Ui::SettingsDialog *ui;
    QSslSocket *sslSocket_;
    bool isConnected_;

};

#endif // SETTINGSDIALOG_H
