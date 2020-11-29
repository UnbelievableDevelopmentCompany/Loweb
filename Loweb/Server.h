#pragma once
#include <QtCore>
#include <QtNetwork>
#include "ConsoleTextStream.h"

class Server : public QObject
{
	Q_OBJECT
public:
	Server(QObject* parent = nullptr);

private slots:
	void SlotNewConnection();

	void SlotReadClient();
private:
	QTcpServer* server;
	quint16 nextBlockSize;
};

