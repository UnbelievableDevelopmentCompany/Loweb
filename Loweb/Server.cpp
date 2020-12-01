#include "Server.h"

Server::Server(QObject* parent) : QObject(parent)
{
	server = new QTcpServer(this);
	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));
}



void Server::SlotNewConnection() {
	QTcpSocket* socket = server->nextPendingConnection();
	qout << "New connection: " << socket->peerAddress().toString() << "\n";
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(SlotReadClient()));
}



Server::~Server()
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
}

void Server::SetHostAddress(const QHostAddress& hostAddress)
{
	_hostAddress = hostAddress;
	_staticFiles.clear();
}



void Server::SetPortServer(const int& port)
{
	_port = port;
}

void Server::SetStaticPath(const QString& path)
{
	_staticPath = path;
	UpdateStaticFiles(_staticPath);
}

void Server::AddView(const QString& path, View* view)
{
	_views[path] = view;
}

void Server::AddStaticFile(const QString& httpPath, const QFile& file)
{
	_staticFiles[httpPath] = file.fileName();
}

void Server::AddStaticFile(const QString& httpPath, const QString& pathToFile)
{
	_staticFiles[httpPath] = pathToFile;
}

EXPORTDLL void Server::AddApplication(Application* app)
{
	_apps.push_back(app);
}



void Server::StartServer()
{
	if (!server->listen(QHostAddress("192.168.0.208"), 3000))
	{
		qout << "Error start server!\n";
		server->close();
		QCoreApplication::quit();
	}
}



void Server::SlotReadClient()
{
	QTcpSocket* socket = dynamic_cast<QTcpSocket*>(sender());

	QString request = socket->readAll();
	qout << request << "\n";
	HttpRequest hrr(request);
	QString path = hrr.GetPath();

	QTextStream os(socket);
	os.setCodec("UTF8");
	QString response;

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
		View* view = item->GetView(path);
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
	}

	response = HttpResponse("Error 404!", 404, "Error").GenerateResponse();
	os << response;
	socket->close();
}

void Server::UpdateStaticFiles(const QString& path)
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
