#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>
#include <QSslSocket>

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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RoomDialog *ui;
};

#endif // ROOMDIALOG_H
