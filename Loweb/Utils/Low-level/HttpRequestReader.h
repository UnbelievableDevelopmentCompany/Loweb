#pragma once
#include <QtCore>

class HttpRequestReader
{
public:
	HttpRequestReader(const QString& httpRequest, bool isProccess = true);

	QString GetPath();
	QString GetMethod();
	QString GetVariable(const QString& varname);

	void Proccess();
private:
	QString _httpRequest;

	QString _path;
	QString _method;
	QMap<QString, QString> _variables;
};

