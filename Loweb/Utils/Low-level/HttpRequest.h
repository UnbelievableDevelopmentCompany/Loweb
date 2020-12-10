#pragma once
#include <QtCore>
#include "../../dll/ExportDLL.h"
#include "../ConsoleTextStream.h"
#include "Session.h"


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
		/// <summary>
		/// Класс, описывающий запрос клиента на сервер.
		/// Он умеет обрабатывать запрос, чтобы все данные получать удобными методами
		/// </summary>
		/// <param name="httpRequest">Сам запрос в виде строки</param>
		/// <param name="session">Текущая сессия, чтобы можно было манипулировать данными сессии откуда угодно</param>
		/// <param name="isProccess"></param>
		EXPORTDLL HttpRequest(const QString& httpRequest, Session* session, bool isProccess = true);


		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		EXPORTDLL QString GetPath();
		EXPORTDLL QString GetMethod();
		EXPORTDLL QString GetVariable(const QString& varname);
		EXPORTDLL QString GetPost(const QString& name);
		EXPORTDLL QString GetGet(const QString& name);
		EXPORTDLL QString GetCookie(const QString& name);
		EXPORTDLL Session* GetSession();

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
	};
}
