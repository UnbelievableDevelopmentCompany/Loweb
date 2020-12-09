#pragma once
#include <QtCore>
#include "../dll/ExportDLL.h"

#include "../Views/View.h"

/// <summary>
/// В данном namespace хранятся классы, которые описывают приложение
/// </summary>
namespace Loweb::Apps
{
	/// <summary>
	/// Базовый класс приложения
	/// </summary>
	class Application
	{
	public:
		EXPORTDLL Application();
		EXPORTDLL Application(Application* parentApp);

		EXPORTDLL virtual ~Application();

		EXPORTDLL void AddView(const QString& path, Views::View* view);
		EXPORTDLL void AddApplication(const QString& path, Application* app);

		EXPORTDLL Views::View* GetView(const QString& path);
		EXPORTDLL Application* GetApplication(const QString& path);
		EXPORTDLL QMap<QString, Application*>& GetApplications();

		EXPORTDLL void SetParentApp(Application* parentApp);
	private:
		QMap<QString, Views::View*> _views;
		QMap<QString, Application*> _apps;
		Application* _parentApp;
	};
}