#include <QtGlobal>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QSettings settings;
    ui->serverAddress->setText(settings.value("serverAddress","127.0.0.1").toString());
    ui->portBox->setValue(settings.value("port",6000).toInt());

    QByteArray username= qgetenv("USER");
    if(! username.isNull())
        ui->userNameEdit->setText(settings.value("username",username).toString());
    else
        ui->userNameEdit->setText(settings.value("username").toString());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::done(int r)
{
    if (r == QDialog::Accepted){
        if(ui->serverAddress->text().isEmpty()){
            QMessageBox::critical(this, "Talk GUI",
                                  "Se necesita la direccion del Servidor");
            return;
        }
        else {
            QSettings settings;
            settings.setValue("serverAddress",ui->serverAddress->text());
            settings.setValue("port",ui->portBox->value());
            if(ui->userNameEdit->text().isEmpty())
                settings.remove("username");
            else
                settings.setValue("username",ui->userNameEdit->text());

            QDialog::done(r);
            return;
        }
    }
    else QDialog::done(r);
}
