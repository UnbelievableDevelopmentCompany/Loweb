#pragma once
#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"

class Server : public QObject
{
	Q_OBJECT
public:
	Server(QObject* parent = nullptr);

	void SetHostAddress(const QHostAddress& hostAddress);
	void SetPortServer(const int& port);

	void StartServer();

private slots:
	void SlotNewConnection();
	void SlotReadClient();
private:
	QTcpServer* server;

	QHostAddress _hostAddress;
	int _port;

};

