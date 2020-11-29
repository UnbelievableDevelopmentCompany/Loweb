#include "Server.h"

Server::Server(QObject* parent = nullptr) : QObject(parent), nextBlockSize(0)
{
	server = new QTcpServer(this);
	if (!server->listen(QHostAddress("192.168.0.208"), 3000))
	{
		qout << "Error start server!\n";
		server->close();
		QCoreApplication::quit();
	}
	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(SlotNewConnection()));
}

void Server::SlotNewConnection() {
	QTcpSocket* socket = server->nextPendingConnection();
	qout << "New connection: " << socket->peerAddress().toString() << "\n";
	QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(SlotReadClient()));
}

void Server::SlotReadClient()
{
	QTcpSocket* socket = (QTcpSocket*)sender();

	QTextStream os(socket);
	os.setCodec("UTF8");
	QString response = u8"HTTP/1.0 200 Ok\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\n<h1> у мир!</h1>\n";

	os << response << QDateTime::currentDateTime().toString();

	qout << socket->readAll() << "\n";

	socket->close();
}