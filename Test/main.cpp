#include <QtCore>
#include <QtNetwork>
#include "Utils/ConsoleTextStream.h"
#include "Utils/render.h"
#include "ProjectConfig.h"

using namespace Loweb;
using namespace Loweb::Utils;

class MyApp : public Apps::Application
{
    class MyView : public Views::View
    {
    public:
        Utils::LowLevel::HttpResponse Get(Utils::LowLevel::HttpRequest& request) override
        {
            return render(request, "hello.html");
        }
        Utils::LowLevel::HttpResponse Post(Utils::LowLevel::HttpRequest& request) override
        {
            return u8"ќу щит ватафак это же пост-запрос!<br> стати, значение переменной myText - " + request.GetPost("myText");
        }
    };
public:
    MyApp()
    {
        this->SetUrlName("");
        this->AddView("/", new Views::View(u8"<a href=\"/hello/\">—сылка</a>"));
        this->AddView("hello/", new MyView);
    }
};

class MyProject : public ProjectConfig
{
public:
    MyProject()
    {
        Config("config.xml");

        AddApplication(new MyApp);

        server.StartServer();
    }
};
int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    
    MyProject p;

    return a.exec();
}
