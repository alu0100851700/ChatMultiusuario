#include "mainwindow.h"
#include <QApplication>
#include <QTcpSocket>


int main(int argc, char *argv[])
{
    //QList<Client*> clients;
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Universidad de La Laguna");
    QApplication::setOrganizationDomain("ull.es");
    QApplication::setApplicationName("Talk GUI");


    MainWindow w;
    w.show();

    return a.exec();
}
