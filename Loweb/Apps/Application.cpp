#include "Application.h"

Loweb::Apps::Application::~Application()
{
	for (auto& item : _views)
	{
		if(item != nullptr)
			delete item;
	}
}

void Loweb::Apps::Application::AddView(const QString& path, Views::View* view)
{
	_views["/" + _urlname + "/" + path] = view;
}

Loweb::Views::View* Loweb::Apps::Application::GetView(const QString& path)
{
	if (_views.contains(path))
		return _views[path];
	return nullptr;
}

const QString& Loweb::Apps::Application::GetUrlName() const
{
	return _urlname;
}

void Loweb::Apps::Application::SetUrlName(const QString& urlname)
{
	_urlname = urlname;
}
