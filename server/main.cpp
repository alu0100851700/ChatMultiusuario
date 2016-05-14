#include <QCoreApplication>
#include <QApplication>
#include <unistd.h>        // para getopt(), optarg, optind, ...
#include <iostream>
#include <QSettings>
#include <QFileInfo>

#include "server.h"

bool fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QApplication::setOrganizationName("Universidad de La Laguna");
    QApplication::setOrganizationDomain("ull.es");
    QApplication::setApplicationName("Servidor Talk");

    int args;
    QSettings settings;

    while ( (args = getopt(argc, argv, "hp:k:c:01")) != -1) {
        switch (args){
            case 'p':
            {
                settings.setValue("port", atoi(optarg));
                break;
            }
            case 'k':
            {
                settings.setValue("sslkey", QString(optarg));
                break;
            }
            case 'c':
            {
                settings.setValue("sslcrt", QString(optarg));
                break;
            }
            case 'h':
            {
                std::cout << "Servidor Talk\n"
                          << "Universidad de La Laguna\n"
                          << "Copyright 2016\n\n"
                          << "Developers\n"
                          << "  Maria Fernanda San Miguel Simik\n"
                          << "  David Fernando Redondo Durand\n\n"
                          << "Usage: server [options]\n\n"
                          << "Set server certificates\n"
                          << "  -k <key>\t.key file\n"
                          << "  -c <key>\t.crt file\n\n"
                          << "Server configuration\n"
                          << "  -p <port>\tserver port"
                          << std::endl;
                return 0;
                break;
            }
            default:
            {
                    std::fprintf(stderr,
                                 "?? getopt devolvió código de error 0%o ??\n",
                                 args);
            }
        }
    }

    if (!fileExists(settings.value("sslkey").toString())){
        std::cerr << "sslkey "
                  << settings.value("sslkey").toString().toUtf8().constData()
                  << " not found" << std::endl;
        return -1;
    }
    if (!fileExists(settings.value("sslcrt").toString())){
        std::cerr << "sslcrt "
                  << settings.value("sslcrt").toString().toUtf8().constData()
                  << " not found" << std::endl;
        return -1;
    }


    Server servidor;


    return a.exec();
}


