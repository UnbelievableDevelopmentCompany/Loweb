#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"
#include "Server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server s;
    s.SetHostAddress(QHostAddress("192.168.0.208"));
    s.SetPortServer(3000);


    s.StartServer();

    return a.exec();
}
