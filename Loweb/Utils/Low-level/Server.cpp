#include "Server.h"
#include "../generateRandomCSRFToken.h"


Loweb::Utils::LowLevel::Server::Server(QObject* parent) : QObject(parent)
{
	server = new QTcpServer(this);
	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));
}



void Loweb::Utils::LowLevel::Server::SlotNewConnection()
{
	QTcpSocket* socket = server->nextPendingConnection();
	ProccessSession(socket);
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(SlotReadClient()));
}



Loweb::Utils::LowLevel::Server::~Server()
{
	for (auto& item : _views)
	{
		if(item != nullptr)
			delete item;
	}

	for (auto& item : _apps)
	{
		if (item != nullptr)
			delete item;
	}

	for (auto& item : _sessions)
	{
		if (item != nullptr)
			delete item;
	}

	if (_config != nullptr)
		delete _config;
}

void Loweb::Utils::LowLevel::Server::SetConfig(Loweb::Config* config)
{
	_config = config;
}

Loweb::Config* Loweb::Utils::LowLevel::Server::GetConfig()
{
	return _config;
}

void Loweb::Utils::LowLevel::Server::SetStaticPath(const QString& path)
{
	_staticFiles.clear();
	_config->staticPath = path;
	UpdateStaticFiles();
}

Loweb::Utils::LowLevel::Session* Loweb::Utils::LowLevel::Server::GetSession(const QString& ipAddress)
{
	// Search session by ip
	auto session = std::find_if(_sessions.begin(), _sessions.end(), [&](Session* a) {
		return a->GetIp() == ipAddress;
	});

	if (session == _sessions.end())
		return nullptr;
	return *session;
}

void Loweb::Utils::LowLevel::Server::AddView(const QString& path, Views::View* view)
{
	view->SetParentApp(nullptr);
	view->SetAbsolutePath(path);
	_views.push_back(view);
}

void Loweb::Utils::LowLevel::Server::AddStaticFile(const QString& httpPath, const QFile& file)
{
	_staticFiles[httpPath] = file.fileName();
}

void Loweb::Utils::LowLevel::Server::AddStaticFile(const QString& httpPath, const QString& pathToFile)
{
	_staticFiles[httpPath] = pathToFile;
}

void Loweb::Utils::LowLevel::Server::AddApplication(const QString& path, Apps::Application* app)
{
	app->SetParentApp(nullptr);
	_apps[path] = app;
}

void Loweb::Utils::LowLevel::Server::Run()
{
	InitializeDatabase();
	UpdateStaticFiles();
	StartServer();
}


void Loweb::Utils::LowLevel::Server::StartServer()
{
	if (!server->listen(_config->hostAddress, _config->hostPort))
	{
		qout << "Error start server!\n" << server->errorString() << "\n";
		server->close();
		exit(0);
	}
}


void Loweb::Utils::LowLevel::Server::SlotReadClient()
{
	QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());

	QTextStream os(socket);
	os.setCodec("UTF8");

	QString request = socket->readAll();
	qout << request << "\n";

	Session* session = GetSession(socket->peerAddress().toString());
	if (session == nullptr)
	{
		qout << "Session error!";
		server->close();
		exit(0);
	}

	HttpRequest httpRequest(request, session, this);

	os << ProccessRequest(httpRequest);
	socket->close();
}

void Loweb::Utils::LowLevel::Server::UpdateStaticFilesByPath(const QString& path)
{
	QDir staticDir(path);
	staticDir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
	if (staticDir.exists())
	{
		QFileInfoList fil = staticDir.entryInfoList();
		for (const auto& item : fil)
		{
			if (item.isDir())
			{
				UpdateStaticFilesByPath(path + "/" + item.fileName());
			}
			else if (item.isFile())
			{
				_staticFiles[item.fileName()] = path + "/" + item.fileName();
			}
		}
	}
}

void Loweb::Utils::LowLevel::Server::UpdateStaticFiles()
{
	UpdateStaticFilesByPath(_config->staticPath);
}

Loweb::Views::View* Loweb::Utils::LowLevel::Server::CheckPathToAppsView(const QString& path, Apps::Application* app, const QString& appUrl)
{
	if (path.startsWith("/" + appUrl))
	{
		QString newPath = path.mid(appUrl.size());

		Views::View* view = app->GetView(newPath.mid(1));
		if (view != nullptr)
		{
			return view;
		}

		for (auto childApp = app->GetApplications().keyValueBegin(); childApp != app->GetApplications().keyValueEnd(); ++childApp)
		{
			view = CheckPathToAppsView(newPath, childApp.base().value(), childApp.base().key());
			return view;
		}
	}
	return nullptr;
}

Loweb::Utils::LowLevel::Session* Loweb::Utils::LowLevel::Server::CreateNewSessionWithCSRFToken(const QString& ip)
{
	return new Session(ip, { {_config->nameCSRFToken, generateRandomCSRFToken(40)} }, QDateTime::currentDateTime().addSecs(15 * 60));
}

void Loweb::Utils::LowLevel::Server::UpdateSession(Loweb::Utils::LowLevel::Session* session)
{
	_sessions.removeOne(session);
	_sessions.push_back(CreateNewSessionWithCSRFToken(session->GetIp()));
	delete session;
}

void Loweb::Utils::LowLevel::Server::ProccessSession(QTcpSocket* socket)
{
	Session* session = GetSession(socket->peerAddress().toString());
	if (session == nullptr)
	{
		_sessions.push_back(CreateNewSessionWithCSRFToken(socket->peerAddress().toString()));
	}
	else if (session->isExpiration())
	{
		UpdateSession(session);
	}
}

void Loweb::Utils::LowLevel::Server::InitializeDatabase()
{
	_database = QSqlDatabase::addDatabase(_config->dbms);
	_database.setDatabaseName(_config->dbName);

	if (!_database.open())
	{
		qout << "Error open database!\n" << _database.lastError().text();
		exit(0);
	}
}

bool Loweb::Utils::LowLevel::Server::CheckCSRFAttack(const Loweb::Utils::LowLevel::HttpRequest& httpRequest, Session* session)
{
	if (httpRequest.GetMethod() == "POST")
	{
		QString tokenFromClient = httpRequest.GetPost(_config->nameCSRFToken);
		QString tokenFromServer = session->GetData(_config->nameCSRFToken);
		return tokenFromClient != tokenFromServer;
	}
	return false;
}

QString Loweb::Utils::LowLevel::Server::ProccessRequest(HttpRequest& httpRequest)
{
	Session* session = httpRequest.GetSession();
	QString path = httpRequest.GetPath();

	if (CheckCSRFAttack(httpRequest, session))
	{
		qout << "CSRF-атака!\n";
		return HttpResponse(u8"CSRF-атака, запрос не был обработан!").GenerateResponse();
	}

	//! Проверка на маршруты уровня проекта
	auto currentViewIterator = std::find_if(_views.begin(), _views.end(), [&](Views::View* view) {
		
	});
	if (_views.contains(path))
	{
		return _views[httpRequest.GetPath()]->Response(httpRequest).GenerateResponse();
	}

	//! Проверка на маршруты уровня приложений
	for (auto app = _apps.keyValueBegin(); app != _apps.keyValueEnd(); ++app)
	{
		Views::View* view = CheckPathToAppsView(path, app.base().value(), app.base().key());
		if (view != nullptr)
		{
			os << view->Response(hrr).GenerateResponse();
			socket->close();
			return;
		}
	}

	//! Проверка на получения статических файлов
	QString staticFileName = path.mid(1, path.size() - (path.endsWith("/") ? 2 : 1));
	if (_staticFiles.contains(staticFileName))
	{
		if (QFileInfo(staticFileName).suffix() == "css")
		{
			QFile staticFile(_staticFiles[staticFileName]);
			staticFile.open(QIODevice::ReadOnly);
			staticFile.close();
			os << HttpResponse(staticFile.readAll()).SetContentType("text/css").GenerateResponse();
			socket->close();
			return;
		}
		else if (QFileInfo(staticFileName).suffix() == "js")
		{
			QFile staticFile(_staticFiles[staticFileName]);
			staticFile.open(QIODevice::ReadOnly);
			staticFile.close();
			os << HttpResponse(staticFile.readAll()).SetContentType("text/javascript").GenerateResponse();
			socket->close();
			return;
		}
	}
}
