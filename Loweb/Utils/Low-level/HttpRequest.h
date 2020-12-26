#pragma once
#include <QtCore>
#include "../../dll/ExportDLL.h"
#include "../ConsoleTextStream.h"
#include "Session.h"

namespace Loweb::Utils::LowLevel
{
	class Server;
}

/// <summary>
/// Тут хранятся низкоуровневые инструменты
/// </summary>
namespace Loweb::Utils::LowLevel
{
	/// <summary>
	/// Класс, описывающий http-запрос с клиента.
	/// </summary>
	class HttpRequest
	{
	public:

		EXPORTDLL HttpRequest(const QString& httpRequest, Session* session, Server* server, bool isProccess = true);

		EXPORTDLL QString GetPath() const;
		EXPORTDLL QString GetMethod() const;
		EXPORTDLL QString GetVariable(const QString& varname) const;
		EXPORTDLL QString GetPost(const QString& name) const;
		EXPORTDLL QString GetGet(const QString& name) const;
		EXPORTDLL QString GetCookie(const QString& name) const;
		EXPORTDLL Session* GetSession() const;
		EXPORTDLL Server* GetServer() const;

		EXPORTDLL void Proccess();
	private:
		QString _httpRequest;

		QString _path;
		QString _method;
		QMap<QString, QString> _variables;
		QMap<QString, QString> _post;
		QMap<QString, QString> _get;

		QMap<QString, QString> _cookies;

		Session* _session;
		Server* _server;
	};
}
