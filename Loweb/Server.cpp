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



void Server::SetHostAddress(const QHostAddress& hostAddress)
{
	_hostAddress = hostAddress;
}



void Server::SetPortServer(const int& port)
{
	_port = port;
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
	qout << request;

	QTextStream os(socket);
	os.setCodec("UTF8");
	QString response = u8"HTTP/1.0 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n";

	QFile htmlFile("D:\\Projects\\C++\\Loweb\\Loweb\\index.html");
	htmlFile.open(QIODevice::ReadOnly);
	response += htmlFile.readAll();

	os << response;
	
	htmlFile.close();
	socket->close();
}