#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"
#include "Server.h"
#include "Utils/render.h"

class MyView : public View
{
public:
    HttpResponse Response(HttpRequest& request) override
    {
        return render(request, "index.html");
    }
};
class MyView2 : public View
{
public:
    HttpResponse Response(HttpRequest& request) override
    {
        return render(request, "index2.html");
    }
};

class MyApp : public Application
{
    class PageOne : public View
    {
    public:
        HttpResponse Response(HttpRequest& request) override
        {
            return HttpResponse("Ogo!");
        }
    };
public:
    MyApp()
    {
        this->SetUrlName("myapp");
        this->AddView("pageOne/", new PageOne);
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
