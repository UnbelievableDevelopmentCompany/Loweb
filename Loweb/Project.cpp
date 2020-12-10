#include "Project.h"

Loweb::Project::Project()
{
	config = new Config;
	server.SetConfig(config);
}

Loweb::Project::~Project()
{
	if (config != nullptr)
		delete config;
}

void Loweb::Project::AddApplication(const QString& path, Apps::Application* application)
{
	server.AddApplication(path, application);
}

void Loweb::Project::AddView(const QString& path, Views::View* view)
{
	server.AddView(path, view);
}

void Loweb::Project::AddStaticFile(const QString& httpPath, const QFile& file)
{
	server.AddStaticFile(httpPath, file);
}

void Loweb::Project::AddStaticFile(const QString& httpPath, const QString& pathToFile)
{
	server.AddStaticFile(httpPath, pathToFile);
}
