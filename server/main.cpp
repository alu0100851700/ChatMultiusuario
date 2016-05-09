#include <QCoreApplication>
#include <QApplication>
#include <QSettings>
#include <unistd.h>

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
                //Desarrollar
                break;
            default:
                    std::fprintf(stderr,
                                 "?? getopt devolvió código de error 0%o ??\n",
                                 args);
        }
    }


    return a.exec();
}
