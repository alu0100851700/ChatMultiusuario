#include "login.h"
#include "roomdialog.h"
#include "ui_login.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);


    QSqlDatabase myDb=QSqlDatabase::addDatabase("QSQLITE");
    myDb.setDatabaseName("/home/mikma/documents/SOA/TalkDefinitivo/ChatMultiusuario/loginDB.sqlite");

    if(!myDb.open())
        ui->statusLabel->setText("Failed to open the database...");
    else
        ui->statusLabel->setText("Connected.");
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    RoomDialog di;
    QString username,password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();


   if(!myDb.isOpen()){
       QString error= myDb.lastError().text();
       ui->statusLabel->setText(error);
       qDebug()<<myDb.lastError();
       //ui->statusLabel->setText("Failed to open the Database");
       return;
    }

    QSqlQuery qry;
    int count=0;

    if(qry.exec("select * from user_table where username='"+username+"' and password='"+password+"'")){
        while(qry.next()){
            count++;
        }

        if(count == 1){
            ui->statusLabel->setText("username and password is correct");
            di.exec();
        }
        if(count > 1)
            ui->statusLabel->setText("Duplicate username and password");
        if(count < 1)
            ui->statusLabel->setText("username and password is not correct");
    }
}
