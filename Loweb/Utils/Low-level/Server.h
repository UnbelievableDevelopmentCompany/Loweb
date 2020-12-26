#pragma once
#include <QtCore>
#include <QtNetwork>

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>

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

		EXPORTDLL void SetStaticPath(const QString& path);
		EXPORTDLL void SetConfig(Config* config);

		EXPORTDLL Config* GetConfig();
		EXPORTDLL Session* GetSession(const QString& ipAddress);

		EXPORTDLL void AddView(const QString& path, Views::View* view);
		EXPORTDLL void AddStaticFile(const QString& httpPath, const QFile& file);
		EXPORTDLL void AddStaticFile(const QString& httpPath, const QString& pathToFile);
		EXPORTDLL void AddApplication(const QString& path, Apps::Application* app);

		EXPORTDLL void Run();

	private slots:
		void SlotNewConnection();
		void SlotReadClient();

	private:
		void StartServer();
		void UpdateStaticFilesByPath(const QString& path);
		void UpdateStaticFiles();
		Views::View* CheckPathToAppsView(const QString& path, Apps::Application* app, const QString& appUrl);
		Session* CreateNewSessionWithCSRFToken(const QString& ip);
		void UpdateSession(Session* session);
		void ProccessSession(QTcpSocket* socket);
		void InitializeDatabase();
		bool CheckCSRFAttack(const HttpRequest& httpRequest, Session* session);
		QString ProccessRequest(HttpRequest& httpRequest);

	private:
		QTcpServer* server;

		QList<Views::View*> _views;
		QMap<QString, QString> _staticFiles;
		QList<Apps::Application*> _apps;
		
		QList<Session*> _sessions;

		Config* _config;
		
		QSqlDatabase _database;
		QSqlQuery _dbQuery;
	};
}
