#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"
#include "Server.h"

class MyView : public View
{
public:
    QString request() override
    {
        QFile file("index.html");
        file.open(QIODevice::ReadOnly);
        QString r = file.readAll();
        file.close();
        return r;
    }
};


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server s;
    s.SetHostAddress(QHostAddress("192.168.0.208"));
    s.SetPortServer(3000);
    s.SetStaticPath("static");

    s.AddView("/", new MyView);

    s.StartServer();

    return a.exec();
}
