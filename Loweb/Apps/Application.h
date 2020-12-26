#pragma once
#include <QtCore>
#include "../dll/ExportDLL.h"

#include "../Views/View.h"

namespace Loweb::Apps
{
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
		EXPORTDLL void SetAbsolutePath(const QString& absolutePath);

		EXPORTDLL QString GetAbsolutePath();
		EXPORTDLL Application* GetParentApp();
	private:

		QList<Views::View*> _views;
		QList<Application*> _apps;

		Application* _parentApp;
		QString _absolutePath;
	};
}