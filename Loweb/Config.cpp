#include "Config.h"

void Loweb::Config::Configure(const QString& pathToConfigXml)
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
					projectName = element.text();
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
								hostAddress = QHostAddress(hostElement.text());
							}
							else if (hostElement.tagName() == "port")
							{
								hostPort = hostElement.text().toInt();
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
								staticPath = element.text();
							}
						}
					}
				}

				else if (element.tagName() == "name-csrf-token")
				{
					nameCSRFToken = element.text();
				}

				else if (element.tagName() == "database")
				{
					QDomNodeList databaseChilds = element.childNodes();
					for (int j = 0; j < databaseChilds.size(); ++j)
					{
						if (databaseChilds.item(j).isElement())
						{
							QDomElement databaseElement = databaseChilds.item(j).toElement();
							if (databaseElement.tagName() == "host-name")
							{
								dbHostName = element.text();
							}
							else if (databaseElement.tagName() == "name")
							{
								dbName = element.text();
							}
							else if (databaseElement.tagName() == "user-name")
							{
								dbUserName = element.text();
							}
							else if (databaseElement.tagName() == "password")
							{
								dbPassword = element.text();
							}
							else if (databaseElement.tagName() == "dbms")
							{
								dbms = element.text();
							}
						}
					}
				}

			}
		}
	}
}