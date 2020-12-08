#include "Server.h"
#include "../generateRandomString.h"

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
		_sessions.push_back(new Session(socket->peerAddress().toString(), { {"CSRF_TOKEN", generateRandomString(30)} }, QDateTime::currentDateTime().addSecs(15*60)));
	}
	else if (session->isExpiration())
	{
		_sessions.removeOne(session);
		_sessions.push_back(new Session(socket->peerAddress().toString(), { {"CSRF_TOKEN", generateRandomString(30)} }, QDateTime::currentDateTime().addSecs(15*60)));
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
}

void Loweb::Utils::LowLevel::Server::SetHostAddress(const QHostAddress& hostAddress)
{
	_hostAddress = hostAddress;
	_staticFiles.clear();
}



void Loweb::Utils::LowLevel::Server::SetHostPort(const int& port)
{
	_port = port;
}

void Loweb::Utils::LowLevel::Server::SetStaticPath(const QString& path)
{
	_staticPath = path;
	UpdateStaticFiles(_staticPath);
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

void Loweb::Utils::LowLevel::Server::AddApplication(Apps::Application* app)
{
	app->SetParentApp(nullptr);
	_apps.push_back(app);
}



void Loweb::Utils::LowLevel::Server::StartServer()
{
	if (!server->listen(_hostAddress, _port))
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
	for (auto& item : _apps)
	{
		Views::View* view = CheckPathToAppsView(path, item);
		if (view != nullptr)
		{
			response = view->Response(hrr).GenerateResponse();
			os << response;
			socket->close();
			return;
		}
	}

	//! Проверка на получения статических файлов
	if (_staticFiles.contains(path.mid(1)))
	{
		if (QFileInfo(path).suffix() == "css")
		{
			QFile staticFile(_staticFiles[path.mid(1)]);
			staticFile.open(QIODevice::ReadOnly);
			response = HttpResponse(staticFile.readAll()).SetContentType("text/css").GenerateResponse();
			staticFile.close();

			os << response;
			socket->close();
			return;
		}
		else if (QFileInfo(path).suffix() == "js")
		{
			QFile staticFile(_staticFiles[path.mid(1)]);
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

Loweb::Views::View* Loweb::Utils::LowLevel::Server::CheckPathToAppsView(const QString& path, Apps::Application* app)
{
	if (path.startsWith("/" + app->GetUrlName()))
	{
		QString newPath = path.mid(app->GetUrlName().size());

		Views::View* view = app->GetView(newPath.mid(1));
		if (view != nullptr)
		{
			return view;
		}

		for (auto& item : app->GetApps())
		{
			view = CheckPathToAppsView(newPath, item);
			return view;
		}
	}
	return nullptr;
}
