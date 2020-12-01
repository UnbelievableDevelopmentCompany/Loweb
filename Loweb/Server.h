#pragma once
#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"
#include "Utils/Low-level/HttpRequest.h"
#include "Views/View.h"
#include "dll/ExportDLL.h"
#include "Apps/Application.h"

class Server : public QObject
{
	Q_OBJECT
public:
	EXPORTDLL Server(QObject* parent = nullptr);
	EXPORTDLL ~Server();

	EXPORTDLL void SetHostAddress(const QHostAddress& hostAddress);
	EXPORTDLL void SetPortServer(const int& port);
	EXPORTDLL void SetStaticPath(const QString& path);

	EXPORTDLL void AddView(const QString& path, View* view);
	EXPORTDLL void AddStaticFile(const QString& httpPath, const QFile& file);
	EXPORTDLL void AddStaticFile(const QString& httpPath, const QString& pathToFile);
	EXPORTDLL void AddApplication(Application* app);

	EXPORTDLL void StartServer();

private slots:
	void SlotNewConnection();
	void SlotReadClient();

private:
	void UpdateStaticFiles(const QString& path);
private:
	QTcpServer* server;

	QHostAddress _hostAddress;
	int _port;

	QMap<QString, View*> _views;
	QMap<QString, QString> _staticFiles;
	QString _staticPath;
	QList<Application*> _apps;
};

