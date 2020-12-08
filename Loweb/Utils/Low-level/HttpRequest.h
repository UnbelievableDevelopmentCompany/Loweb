#pragma once
#include <QtCore>
#include "../../dll/ExportDLL.h"
#include "../ConsoleTextStream.h"
#include "Session.h"

namespace Loweb::Utils::LowLevel
{
	class HttpRequest
	{
	public:
		EXPORTDLL HttpRequest(const QString& httpRequest, Session* session, bool isProccess = true);

		EXPORTDLL QString GetPath();
		EXPORTDLL QString GetMethod();
		EXPORTDLL QString GetVariable(const QString& varname);
		EXPORTDLL QString GetPost(const QString& name);
		EXPORTDLL QString GetGet(const QString& name);
		EXPORTDLL Session* GetSession();

		EXPORTDLL void Proccess();
	private:
		QString _httpRequest;

		QString _path;
		QString _method;
		QMap<QString, QString> _variables;
		QMap<QString, QString> _post;
		QMap<QString, QString> _get;

		Session* _session;
	};
}
