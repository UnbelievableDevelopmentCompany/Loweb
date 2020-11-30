#include "Application.h"

Application::~Application()
{
	for (auto& item : _views)
	{
		if(item != nullptr)
			delete item;
	}
}

EXPORTDLL void Application::AddView(const QString& path, View* view)
{
	_views[path] = view;
}

EXPORTDLL View* Application::GetView(const QString& path)
{
	if (_views.contains(path))
		return _views[path];
	return nullptr;
}

EXPORTDLL const QString& Application::GetUrlName() const
{
	return _urlname;
}

EXPORTDLL void Application::SetUrlName(const QString& urlname)
{
	_urlname = urlname;
}
