#include "ProjectConfig.h"

void Loweb::ProjectConfig::SetProjectName(const QString& projectName)
{
	_projectName = projectName;
}

void Loweb::ProjectConfig::SetHostAddress(const QHostAddress& hostAddress)
{
	server.SetHostAddress(hostAddress);
}

void Loweb::ProjectConfig::SetHostPort(const quint16& port)
{
	server.SetHostPort(port);
}

void Loweb::ProjectConfig::SetStaticPath(const QString& staticPath)
{
	server.SetStaticPath(staticPath);
}

EXPORTDLL void Loweb::ProjectConfig::Config(const QString& pathToConfigXml)
{
	QFile configFile(pathToConfigXml);
	if (!configFile.open(QIODevice::ReadOnly))
	{
		qout << "Error open config-file: " << pathToConfigXml;
		exit(0);
	}
	QDomDocument domDocument;
	domDocument.setContent(&configFile);
	QDomElement rootElement = domDocument.documentElement();

	if (rootElement.tagName() == "project")
	{
		QDomNodeList childs = rootElement.childNodes();
		for (int i = 0; i < childs.size(); ++i)
		{
			if (childs.item(i).isElement())
			{
				QDomElement element = childs.item(i).toElement();
				if (element.tagName() == "name")
				{
					SetProjectName(element.text());
				}

				else if (element.tagName() == "host")
				{
					QDomNodeList hostChilds = element.childNodes();
					for (int j = 0; j < hostChilds.size(); ++j)
					{
						if (hostChilds.item(j).isElement())
						{
							QDomElement hostElement = hostChilds.item(j).toElement();
							if (hostElement.tagName() == "address")
							{
								SetHostAddress(QHostAddress(hostElement.text()));
							}
							else if (hostElement.tagName() == "port")
							{
								SetHostPort(hostElement.text().toInt());
							}
						}
					}
				}

				else if (element.tagName() == "static-files")
				{
					QDomNodeList staticFilesChilds = element.childNodes();
					for (int j = 0; j < staticFilesChilds.size(); ++j)
					{
						if (staticFilesChilds.item(j).isElement())
						{
							QDomElement staticFilesElement = staticFilesChilds.item(j).toElement();
							if (staticFilesElement.tagName() == "path")
							{
								SetStaticPath(element.text());
							}
						}
					}
				}
			}
		}
	}
}

void Loweb::ProjectConfig::AddApplication(const QString& path, Apps::Application* application)
{
	server.AddApplication(path, application);
}

void Loweb::ProjectConfig::AddView(const QString& path, Views::View* view)
{
	server.AddView(path, view);
}

EXPORTDLL void Loweb::ProjectConfig::AddStaticFile(const QString& httpPath, const QFile& file)
{
	server.AddStaticFile(httpPath, file);
}

EXPORTDLL void Loweb::ProjectConfig::AddStaticFile(const QString& httpPath, const QString& pathToFile)
{
	server.AddStaticFile(httpPath, pathToFile);
}
