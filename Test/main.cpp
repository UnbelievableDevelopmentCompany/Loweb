#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"
#include "Server.h"
#include "Utils/render.h"

class MyView : public View
{
public:
    QString Response(HttpRequestReader& request) override
    {
        return render(request, "index.html");
    }
};
class MyView2 : public View
{
public:
    QString Response(HttpRequestReader& request) override
    {
        return render(request, "index2.html");
    }
};

class MyApp : public Application
{
    class PageOne : public View
    {
    public:
        QString Response(HttpRequestReader& request) override
        {
            return render(request, "pageOne.html");
        }
    };
public:
    MyApp()
    {
        this->AddView("pageOne", new PageOne);
        this->SetUrlName("myapp");
    }
};


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    Server s;
    s.SetHostAddress(QHostAddress("192.168.0.208"));
    s.SetPortServer(3000);
    s.SetStaticPath("static");

    s.AddApplication(new MyApp);

    s.AddView("/", new MyView);
    s.AddView("/two/", new MyView2);

    s.StartServer();

    return a.exec();
}
