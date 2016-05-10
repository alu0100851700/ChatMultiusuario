#include <QCoreApplication>
#include <QApplication>
#include <unistd.h>        // para getopt(), optarg, optind, ...
#include <iostream>
#include <QSettings>

#include "server.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QApplication::setOrganizationName("Universidad de La Laguna");
    QApplication::setOrganizationDomain("ull.es");
    QApplication::setApplicationName("Servidor Talk");

    int args;
    QSettings settings;

    while ( (args = getopt(argc, argv, "p:01")) != -1) {
        switch (args){
            case 'p':
                settings.setValue("port", atoi(optarg));
                break;
            case 'h':
                std::cout << "Ayuda en desarrollo" << std::endl;
                break;
            default:
                    std::fprintf(stderr,
                                 "?? getopt devolvió código de error 0%o ??\n",
                                 args);
        }
    }


    Server servidor;


    return a.exec();
}
