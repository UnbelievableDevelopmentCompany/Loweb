#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"
#include "Server.h"
#include "Utils/render.h"
#include "Utils/ProjectConfig.h"


class MyView : public View
{
public:
    HttpResponse Response(HttpRequest& request) override
    {
        return render(request, "index.html", { {"MyVar", "Hello world"}, {"MyVar2", "hello lofectr!"} });
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

class MyProject : public ProjectConfig
{
public:
    MyProject()
    {
        SetHostAddress(QHostAddress("192.168.0.208"));
        SetHostPort(3000);
        SetStaticPath("static");

        AddApplication(new MyApp);

        AddView("/", new MyView);
        AddView("/two/", new MyView2);

        server.StartServer();
    }
};
int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    
    MyProject p;

    return a.exec();
}
