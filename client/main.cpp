#include "mainwindow.h"
#include "login.h"
#include "settingsdialog.h"
#include <QApplication>
#include <QTcpSocket>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    QApplication::setOrganizationName("Universidad de La Laguna");
    QApplication::setOrganizationDomain("ull.es");
    QApplication::setApplicationName("Talk GUI");

    SettingsDialog se;
    se.show();

    return a.exec();
}
