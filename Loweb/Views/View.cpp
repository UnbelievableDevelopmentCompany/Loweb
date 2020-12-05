#include "View.h"

Loweb::Views::View::View(const QString& response) : _response(response)
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
