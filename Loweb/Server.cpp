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
	HttpRequestReader hrr(request);
	QString path = hrr.GetPath();

	QTextStream os(socket);
	os.setCodec("UTF8");
	QString response;// = u8"HTTP/1.1 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n";

	if (_views.contains(path))
	{
		response = "HTTP/1.1 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n";
		response += _views[path]->Response(hrr);
	}
	else if (_staticFiles.contains(path.mid(1)))
	{
		if (QFileInfo(path).suffix() == "css")
		{
			response = "HTTP/1.1 200 Ok\r\nContent-Type: text/css; charset=\"utf-8\"\r\n\r\n";
			QFile staticFile(_staticFiles[path.mid(1)]);
			staticFile.open(QIODevice::ReadOnly);
			response += staticFile.readAll();
			staticFile.close();
		}
	}

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
