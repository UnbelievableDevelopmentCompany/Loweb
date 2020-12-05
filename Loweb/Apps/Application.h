#pragma once
#include <QtCore>
#include "../dll/ExportDLL.h"
#include "../Views/View.h"

namespace Loweb::Apps
{
	class Application
	{
	public:
		EXPORTDLL virtual ~Application();

		EXPORTDLL void AddView(const QString& path, Views::View* view);

		EXPORTDLL Views::View* GetView(const QString& path);
		EXPORTDLL const QString& GetUrlName() const;

		EXPORTDLL void SetUrlName(const QString& urlname);
	private:
		QMap<QString, Views::View*> _views;
		QString _urlname;
	};
}