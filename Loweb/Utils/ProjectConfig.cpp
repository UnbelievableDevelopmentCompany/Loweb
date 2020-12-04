#include "ProjectConfig.h"

void ProjectConfig::SetProjectName(const QString& projectName)
{
	_projectName = projectName;
}

void ProjectConfig::SetHostAddress(const QHostAddress& hostAddress)
{
	server.SetHostAddress(hostAddress);
}

void ProjectConfig::SetHostPort(const quint16& port)
{
	server.SetHostPort(port);
}

void ProjectConfig::SetStaticPath(const QString& staticPath)
{
	server.SetStaticPath(staticPath);
}

EXPORTDLL void ProjectConfig::Config(const QString& pathToConfigXml)
{
	//TODO
}

void ProjectConfig::AddApplication(Application* application)
{
	server.AddApplication(application);
}

void ProjectConfig::AddView(const QString& path, View* view)
{
	server.AddView(path, view);
}

EXPORTDLL void ProjectConfig::AddStaticFile(const QString& httpPath, const QFile& file)
{
	server.AddStaticFile(httpPath, file);
}

EXPORTDLL void ProjectConfig::AddStaticFile(const QString& httpPath, const QString& pathToFile)
{
	server.AddStaticFile(httpPath, pathToFile);
}
