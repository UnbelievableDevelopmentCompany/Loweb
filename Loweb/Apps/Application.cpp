#include "Application.h"

Loweb::Apps::Application::Application() : _parentApp(nullptr)
{
}

Loweb::Apps::Application::Application(Application* parentApp) : _parentApp(parentApp)
{
}

Loweb::Apps::Application::~Application()
{
	// При удалении объекта application будут удалены его views и apps.
	// Объект удаляется при остановке сервера.
	for (auto& item : _views)
	{
		if(item != nullptr)
			delete item;
	}

	for (auto& item : _apps)
	{
		if (item != nullptr)
			delete item;
	}
}

void Loweb::Apps::Application::AddView(const QString& path, Views::View* view)
{
	// При добавлении view в приложение надо задать ему его родителя, то есть this
	view->SetParentApp(this);

	_views[path] = view;
}

void Loweb::Apps::Application::AddApplication(const QString& path, Application* app)
{
	// При добавлении приложения в приложение надо задать ему его родителя, то есть this
	app->SetParentApp(this);

	_apps[path] = app;
}

Loweb::Views::View* Loweb::Apps::Application::GetView(const QString& path)
{
	if (_views.contains(path))
		return _views[path];
	return nullptr;
}

Loweb::Apps::Application* Loweb::Apps::Application::GetApplication(const QString& path)
{
	if (_apps.contains(path))
		return _apps[path];
	return nullptr;
}

QMap<QString, Loweb::Apps::Application*>& Loweb::Apps::Application::GetApplications()
{
	return _apps;
}

void Loweb::Apps::Application::SetParentApp(Application* parentApp)
{
	_parentApp = parentApp;
}
