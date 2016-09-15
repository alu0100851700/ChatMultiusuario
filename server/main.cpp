#include <QCoreApplication>
#include <QApplication>
#include <unistd.h>        // para getopt(), optarg, optind, ...
#include <iostream>
#include <QSettings>
#include <QFileInfo>
#include <QDir>

#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <clocale>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <fstream>

#include "server.h"

#include <syslog.h>

#define O_RDONLY         00
#define O_WRONLY         01
#define O_RDWR           02

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
    bool daemon = true;
    QSettings settings;

    while ( (args = getopt(argc, argv, "thp:k:c:01")) != -1) {
        switch (args){
            case 't':
            {
                daemon = false;
                break;
            }
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
                          << "  -p <port>\tserver port\n"
                          << "Terminal\n"
                          << "  -t\t\tRun Server in terminal\n"
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

    if (daemon){
        pid_t pid;

        // Nos clonamos a nosotros mismos creando un proceso hijo
        pid = fork();

        // Si pid es < 0, fork() falló
        if (pid < 0) {
            // Mostrar la descripción del error y terminar
            std::cerr << std::strerror(errno) << '\n';
            exit(10);
        }

        // Si pid es > 0, estamos en el proceso padre
        if (pid > 0) {
            // Terminar el proceso
            exit(0);
        }

        // Si la ejecución llega a este punto, estamos en el hijo
/*

        openlog(argv[0], LOG_NOWAIT | LOG_PID, LOG_USER);

        // Cambiar el directorio de trabajo de proceso
        if ((chdir("/")) < 0) {
            syslog(LOG_ERR, "No fue posible cambiar el directorio de trabajo a /\n");
            exit(12);
        }

        pid_t sid;

        // Intentar crear una nueva sesión
        sid = setsid();
        if (sid < 0) {
            syslog(LOG_ERR, "No fue posible crear una nueva sesión\n");
            exit(11);
        }

        // Cambiar el usuario efectivo del proceso a 'midemonio'
        passwd* user = getpwnam("talkServer");
        seteuid(user->pw_uid);

        // Cambiar el grupo efectivo del proceso a 'midemonio'
        group* group = getgrnam("talkServer");
        setegid(group->gr_gid);
*/
        // Cerrar los descriptores de la E/S estándar
        close(STDIN_FILENO);                    // fd 0
        close(STDOUT_FILENO);                   // fd 1
        close(STDERR_FILENO);                   // fd 2
/*
        int fd0 = open("/dev/null", O_RDONLY);  // fd0 == 0
        int fd1 = open("/dev/null", O_WRONLY);  // fd0 == 1
        int fd2 = open("/dev/null", O_WRONLY);  // fd0 == 2
*/
    }

    if (!fileExists(settings.value("sslkey").toString()))
        settings.setValue("sslkey", QDir::currentPath() + "/certificate/server.key");

    if (!fileExists(settings.value("sslkey").toString())){
        std::cerr << "sslkey "
                  << settings.value("sslkey").toString().toUtf8().constData()
                  << " not found" << std::endl;
        return -1;
    }

    if (!fileExists(settings.value("sslcrt").toString()))
        settings.setValue("sslcrt",QDir::currentPath() + "/certificate/server.crt");
    if (!fileExists(settings.value("sslcrt").toString())){
        std::cerr << "sslcrt "
                  << settings.value("sslcrt").toString().toUtf8().constData()
                  << " not found" << std::endl;
        return -1;
    }


    Server servidor;


    return a.exec();
}


