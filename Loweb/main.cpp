#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"
#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server s;

    return a.exec();
}
