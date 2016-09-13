#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>
#include <QSslSocket>
#include <QSettings>
#include <QDateTime>
#include <mainwindow.h>

#include "talkmessage.pb.h"



namespace Ui {
class RoomDialog;
}

class RoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RoomDialog(QWidget *parent = 0);
    ~RoomDialog();
     void initializeSocket(QSslSocket* sslSocket);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::RoomDialog *ui;
    QSslSocket *sslSocket_;


};

#endif // ROOMDIALOG_H
