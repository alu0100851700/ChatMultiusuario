#include "mainwindow.h"
#include "login.h"
#include "settingsdialog.h"
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

    /*MainWindow w;
    w.show();*/

   /* Login z;
    z.show();*/

    SettingsDialog se;
    se.show();

    return a.exec();
}
