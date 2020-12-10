#include <QtCore>
#include <QtNetwork>
#include "Utils/ConsoleTextStream.h"
#include "Utils/render.h"
#include "ProjectConfig.h"

using namespace Loweb;
using namespace Loweb::Utils;

class MyApp : public Apps::Application
{
    class Test : public Application
    {
    public:
        Test()
        {
            AddView("", new Views::View("Ha-ha"));
        }
    };
    class MyView : public Views::View
    {
    public:
        Utils::LowLevel::HttpResponse Get(Utils::LowLevel::HttpRequest& request) override
        {
            QMap<QString, QString> context;

            context["data"] = "Anatar loh";

            return render(request, "hello.html", context);
        }
        Utils::LowLevel::HttpResponse Post(Utils::LowLevel::HttpRequest& request) override
        {
            QMap<QString, QString> context;
            context["data"] = request.GetPost("myText");
            return render(request, "hello.html", context);
        }
    };
public:
    MyApp()
    {
        AddApplication("ha-ha/", new Test);
        this->AddView("four/", new Views::View(u8"<a href=\"/hello/\">—сылка</a>"));
        this->AddView("hello/", new MyView);
    }
};

class MyProject : public ProjectConfig
{
public:
    MyProject()
    {
        Config("config.xml");

        AddApplication("hello/", new MyApp);

        server.StartServer();
    }
};
int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    
    MyProject p;

    return a.exec();
}
