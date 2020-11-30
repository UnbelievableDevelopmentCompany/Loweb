#pragma once
#include <QtCore>
#include "../dll/ExportDLL.h"
#include "../Views/View.h"


class Application
{
public:
	EXPORTDLL ~Application();

	EXPORTDLL void AddView(const QString& path, View* view);

	EXPORTDLL View* GetView(const QString& path);
	EXPORTDLL const QString& GetUrlName() const;

	EXPORTDLL void SetUrlName(const QString& urlname);
private:
	QMap<QString, View*> _views;
	QString _urlname;
};

