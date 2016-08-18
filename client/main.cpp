#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QTcpSocket>



int main(int argc, char *argv[])
{
    //QList<Client*> clients;
    QApplication a(argc, argv);
    a.setStyle("fusion");
    QApplication::setOrganizationName("Universidad de La Laguna");
    QApplication::setOrganizationDomain("ull.es");
    QApplication::setApplicationName("Talk GUI");


    /*Login w;
    w.show();*/

    MainWindow w;
    w.show();

    return a.exec();
}
