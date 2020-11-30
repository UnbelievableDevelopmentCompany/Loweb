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
	for (View* item : _views)
	{
		delete item;
	}
}

void Server::SetHostAddress(const QHostAddress& hostAddress)
{
	_hostAddress = hostAddress;
}



void Server::SetPortServer(const int& port)
{
	_port = port;
}

void Server::AddView(const QString& path, View* view)
{
	_views[path] = view;
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
	HttpRequestReader h(request);
	QString path = h.GetPath();

	QTextStream os(socket);
	os.setCodec("UTF8");
	QString response = u8"HTTP/1.1 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n";

	QFile htmlFile("");
	htmlFile.open(QIODevice::ReadOnly);
	response += htmlFile.readAll();

	os << response;
	
	htmlFile.close();
	socket->close();
}