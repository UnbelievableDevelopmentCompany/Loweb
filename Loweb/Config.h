#pragma once
#include <QtNetwork>
#include <QtXml/qdom.h>
#include "dll/ExportDLL.h"
#include "Utils/ConsoleTextStream.h"

namespace Loweb
{
	struct Config
	{
		QHostAddress hostAddress = QHostAddress("localhost");
		quint16 hostPort = 80;
		QString projectName = "newLowebProject";
		QString staticPath = "static";
		QString nameCSRFToken = "CSRF_TOKEN";


		EXPORTDLL void Configure(const QString& pathToConfigXml);
		
	};
}