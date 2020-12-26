#include "View.h"

Loweb::Views::View::View(const QString& response, Loweb::Apps::Application* parentApp)
	: _response(response), _parentApp(parentApp)
{
}

Loweb::Views::View::View(Loweb::Apps::Application* parentApp) : _parentApp(parentApp)
{
}

Loweb::Views::View::View() : _response("")
{
}

Loweb::Utils::LowLevel::HttpResponse Loweb::Views::View::Response(Utils::LowLevel::HttpRequest& request)
{
	if (request.GetMethod() == "GET")
	{
		return Get(request);
	}
	else if (request.GetMethod() == "POST")
	{
		return Post(request);
	}
	else
	{
		return u8"Необработаный метод " + request.GetMethod();
	}
}

Loweb::Utils::LowLevel::HttpResponse Loweb::Views::View::Get(Utils::LowLevel::HttpRequest& request)
{
	return _response;
}

Loweb::Utils::LowLevel::HttpResponse Loweb::Views::View::Post(Utils::LowLevel::HttpRequest& request)
{
	return _response;
}

void Loweb::Views::View::SetParentApp(Apps::Application* app)
{
	_parentApp = app;
}

void Loweb::Views::View::SetAbsolutePath(const QString& absolutePath)
{
	_absolutePath = absolutePath;
}
