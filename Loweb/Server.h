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
	void SetStaticPath(const QString& path);

	void AddView(const QString& path, View* view);
	void AddStaticFile(const QString& httpPath, const QFile& file);
	void AddStaticFile(const QString& httpPath, const QString& pathToFile);

	void StartServer();

private slots:
	void SlotNewConnection();
	void SlotReadClient();

private:
	void UpdateStaticFiles(const QString& path);
private:
	QTcpServer* server;

	QHostAddress _hostAddress;
	int _port;

	QMap<QString, View*> _views;
	QMap<QString, QString> _staticFiles;
	QString _staticPath;
};

