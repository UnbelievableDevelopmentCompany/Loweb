#include "Server.h"
#include "../generateRandomCSRFToken.h"


Loweb::Utils::LowLevel::Server::Server(QObject* parent) : QObject(parent)
{
	server = new QTcpServer(this);
	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));
}



void Loweb::Utils::LowLevel::Server::SlotNewConnection() {
	QTcpSocket* socket = server->nextPendingConnection();

	Session* session = GetSession(socket->peerAddress().toString());
	if (session == nullptr)
	{
		_sessions.push_back(new Session(socket->peerAddress().toString(), { {"CSRF_TOKEN", generateRandomCSRFToken(40)} }, QDateTime::currentDateTime().addSecs(15*60)));
	}
	else if (session->isExpiration())
	{
		_sessions.removeOne(session);
		_sessions.push_back(new Session(socket->peerAddress().toString(), { {"CSRF_TOKEN", generateRandomCSRFToken(40)} }, QDateTime::currentDateTime().addSecs(15*60)));
	}

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

void Loweb::Utils::LowLevel::Server::SetHostAddress(const QHostAddress& hostAddress)
{
	_config->hostAddress = hostAddress;
	_staticFiles.clear();
}


void Loweb::Utils::LowLevel::Server::SetHostPort(const int& port)
{
	_config->hostPort = port;
}

void Loweb::Utils::LowLevel::Server::SetStaticPath(const QString& path)
{
	_config->staticPath = path;
	UpdateStaticFiles(_config->staticPath);
}

Loweb::Utils::LowLevel::Session* Loweb::Utils::LowLevel::Server::GetSession(const QString& ipAddress)
{
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
	_views[path] = view;
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



void Loweb::Utils::LowLevel::Server::StartServer()
{
	UpdateStaticFiles(_config->staticPath);
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

	QString request = socket->readAll();
	qout << request << "\n";

	Session* session = GetSession(socket->peerAddress().toString());
	if (session == nullptr)
	{
		qout << "Session error!";
		server->close();
		exit(0);
	}

	HttpRequest hrr(request, session);
	QString path = hrr.GetPath();

	QTextStream os(socket);
	os.setCodec("UTF8");
	QString response;


	//! CSRF-проверка
	if (hrr.GetMethod() == "POST")
	{
		QString tokenFromClient = hrr.GetPost("CSRF_TOKEN");

		QString tokenFromServer = session->GetData("CSRF_TOKEN");

		if (tokenFromClient != tokenFromServer)
		{
			// Значит происходит csrf-атака!
			qout << "CSRF-атака!\n";
			response = HttpResponse(u8"CSRF-атака, запрос не был обработан!").GenerateResponse();
			os << response;
			socket->close();
			return;
		}
	}

	//! Проверка на маршруты уровня проекта
	if (_views.contains(path))
	{
		response = _views[path]->Response(hrr).GenerateResponse();

		os << response;
		socket->close();
		return;
	}

	//! Проверка на маршруты уровня приложений
	for (auto app = _apps.keyValueBegin(); app != _apps.keyValueEnd(); ++app)
	{
		Views::View* view = CheckPathToAppsView(path, app.base().value(), app.base().key());
		if (view != nullptr)
		{
			response = view->Response(hrr).GenerateResponse();
			os << response;
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
			response = HttpResponse(staticFile.readAll()).SetContentType("text/css").GenerateResponse();
			staticFile.close();

			os << response;
			socket->close();
			return;
		}
		else if (QFileInfo(staticFileName).suffix() == "js")
		{
			QFile staticFile(_staticFiles[staticFileName]);
			staticFile.open(QIODevice::ReadOnly);
			response = HttpResponse(staticFile.readAll()).SetContentType("text/javascript").GenerateResponse();
			staticFile.close();

			os << response;
			socket->close();
			return;
		}
	}

	response = HttpResponse("Error 404!", 404, "Error").GenerateResponse();
	os << response;
	socket->close();
}

void Loweb::Utils::LowLevel::Server::UpdateStaticFiles(const QString& path)
{
	QDir staticDir(path);
	staticDir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
	if (staticDir.exists())
	{
		QFileInfoList fil = staticDir.entryInfoList();
		for (auto item : fil)
		{
			if (item.isDir())
			{
				UpdateStaticFiles(path + "/" + item.fileName());
			}
			else if (item.isFile())
			{
				_staticFiles[item.fileName()] = path + "/" + item.fileName();
			}
		}
	}
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
