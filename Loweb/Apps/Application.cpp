#include "Application.h"

Loweb::Apps::Application::Application()
{
}

Loweb::Apps::Application::Application(Application* parentApp) : _parentApp(parentApp)
{
}

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
	view->SetParentApp(this);

	_views[path] = view;
}

void Loweb::Apps::Application::AddApplication(Application* app)
{
	app->SetParentApp(this);
	_apps.push_back(app);
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

QList<Loweb::Apps::Application*>& Loweb::Apps::Application::GetApps()
{
	return _apps;
}

void Loweb::Apps::Application::SetUrlName(const QString& urlname)
{
	_urlname = urlname;
}

void Loweb::Apps::Application::SetParentApp(Application* parentApp)
{
	_parentApp = parentApp;
}
