#pragma once
#include <QtCore>
#include <QtNetwork>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include "../ConsoleTextStream.h"
#include "HttpRequest.h"
#include "../../Views/View.h"
#include "../../dll/ExportDLL.h"
#include "../../Apps/Application.h"
#include "Session.h"
#include "../../Config.h"

namespace Loweb::Utils::LowLevel
{
	class Server : public QObject
	{
		Q_OBJECT
	public:
		EXPORTDLL Server(QObject* parent = nullptr);
		EXPORTDLL virtual ~Server();

		EXPORTDLL void SetConfig(Loweb::Config* config);
		EXPORTDLL Config* GetConfig();

		EXPORTDLL void SetHostAddress(const QHostAddress& hostAddress);
		EXPORTDLL void SetHostPort(const int& port);
		EXPORTDLL void SetStaticPath(const QString& path);

		EXPORTDLL Session* GetSession(const QString& ipAddress);

		EXPORTDLL void AddView(const QString& path, Views::View* view);
		EXPORTDLL void AddStaticFile(const QString& httpPath, const QFile& file);
		EXPORTDLL void AddStaticFile(const QString& httpPath, const QString& pathToFile);
		EXPORTDLL void AddApplication(const QString& path, Apps::Application* app);

		EXPORTDLL void StartServer();

	private slots:
		void SlotNewConnection();
		void SlotReadClient();

	private:
		void UpdateStaticFiles(const QString& path);
		Views::View* CheckPathToAppsView(const QString& path, Apps::Application* app, const QString& appUrl);
	private:
		QTcpServer* server;

		QMap<QString, Views::View*> _views;
		QMap<QString, QString> _staticFiles;
		QMap<QString, Apps::Application*> _apps;
		
		QList<Session*> _sessions;

		Config* _config;
		
		QSqlDatabase _database;
		QSqlQuery _dbQuery;
	};
}
