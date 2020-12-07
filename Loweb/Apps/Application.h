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
		EXPORTDLL void AddApplication(Application* app);

		EXPORTDLL Views::View* GetView(const QString& path);
		EXPORTDLL const QString& GetUrlName() const;
		EXPORTDLL QList<Application*>& GetApps();

		EXPORTDLL void SetUrlName(const QString& urlname);

		EXPORTDLL void SetParentApp(Application* parentApp);
	private:
		QMap<QString, Views::View*> _views;
		QList<Application*> _apps;
		QString _urlname;
		Application* _parentApp;
	};
}