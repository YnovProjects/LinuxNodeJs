#include <QCoreApplication>
#include "serveur.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Serveur serv;
    serv.start();
    return a.exec();
}
