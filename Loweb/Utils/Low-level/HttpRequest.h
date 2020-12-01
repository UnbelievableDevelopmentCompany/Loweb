﻿#pragma once
#include <QtCore>
#include "../../dll/ExportDLL.h"

class HttpRequest
{
public:
	EXPORTDLL HttpRequest(const QString& httpRequest, bool isProccess = true);

	EXPORTDLL QString GetPath();
	EXPORTDLL QString GetMethod();
	EXPORTDLL QString GetVariable(const QString& varname);

	EXPORTDLL void Proccess();
private:
	QString _httpRequest;

	QString _path;
	QString _method;
	QMap<QString, QString> _variables;
};
