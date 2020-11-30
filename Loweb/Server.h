#pragma once
#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"
#include "Utils/Low-level/HttpRequestReader.h"
#include "Views/View.h"

class Server : public QObject
{
	Q_OBJECT
public:
	Server(QObject* parent = nullptr);
	~Server();

	void SetHostAddress(const QHostAddress& hostAddress);
	void SetPortServer(const int& port);

	void AddView(const QString& path, View* view);

	void StartServer();

private slots:
	void SlotNewConnection();
	void SlotReadClient();
private:
	QTcpServer* server;

	QHostAddress _hostAddress;
	int _port;

	QMap<QString, View*> _views;
};

