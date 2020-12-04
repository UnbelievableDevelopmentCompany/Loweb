#pragma once
#include <QtCore>
#include "../Server.h"

class ProjectConfig
{
public:
	EXPORTDLL void SetProjectName(const QString& projectName);
	EXPORTDLL void SetHostAddress(const QHostAddress& hostAddress);
	EXPORTDLL void SetHostPort(const quint16& port);
	EXPORTDLL void SetStaticPath(const QString& staticPath);
	EXPORTDLL void Config(const QString& pathToConfigXml);

	EXPORTDLL void AddApplication(Application* application);
	EXPORTDLL void AddView(const QString& path, View* view);
	EXPORTDLL void AddStaticFile(const QString& httpPath, const QFile& file);
	EXPORTDLL void AddStaticFile(const QString& httpPath, const QString& pathToFile);
private:
	QString _projectName;
protected:
	Server server;
};
