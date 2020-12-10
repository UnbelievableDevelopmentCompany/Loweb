#pragma once
#include <QtCore>
#include <QtXml/qdom.h>
#include "Utils/Low-level/Server.h"
#include "Config.h"

namespace Loweb
{
	class Project
	{
	public:
		EXPORTDLL Project();
		EXPORTDLL virtual ~Project();

		EXPORTDLL void AddApplication(const QString& path, Apps::Application* application);
		EXPORTDLL void AddView(const QString& path, Views::View* view);
		EXPORTDLL void AddStaticFile(const QString& httpPath, const QFile& file);
		EXPORTDLL void AddStaticFile(const QString& httpPath, const QString& pathToFile);
	protected:
		Loweb::Utils::LowLevel::Server server;
		Loweb::Config* config;
	};
}