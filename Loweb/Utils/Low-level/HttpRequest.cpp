#include "HttpRequest.h"

Loweb::Utils::LowLevel::HttpRequest::HttpRequest(const QString& httpRequest, Loweb::Utils::LowLevel::Session* session, bool isProccess)
	:_session(session)
{
	_httpRequest = httpRequest;
	if (isProccess)
		Proccess();
}

QString Loweb::Utils::LowLevel::HttpRequest::GetPath()
{
	return _path;
}

QString Loweb::Utils::LowLevel::HttpRequest::GetMethod()
{
	return _method;
}

QString Loweb::Utils::LowLevel::HttpRequest::GetVariable(const QString& varname)
{
	return _variables[varname];
}

QString Loweb::Utils::LowLevel::HttpRequest::GetPost(const QString& name)
{
	return _post[name];
}

QString Loweb::Utils::LowLevel::HttpRequest::GetGet(const QString& name)
{
	return _get[name];
}

Loweb::Utils::LowLevel::Session* Loweb::Utils::LowLevel::HttpRequest::GetSession()
{
	return _session;
}

void Loweb::Utils::LowLevel::HttpRequest::Proccess()
{
	QStringList lines = _httpRequest.split("\r\n");

	QStringList postVariables;
	if (lines[lines.size() - 2] == "")
	{
		postVariables = lines.back().split("&");
		lines.pop_back();
		lines.pop_back();
	}

	lines.removeAll("");
	QStringList firstLine = lines[0].split(" ");
	lines.pop_front();
	_method = firstLine[0];
	_path = firstLine[1];

	QStringList temp;
	for (auto& item : lines)
	{
		temp = item.split(": ");
		_variables[temp[0]] = temp[1];
	}

	if (_method == "POST")
	{
		temp.clear();
		for (auto& item : postVariables)
		{
			temp = item.split("=");
			_post[temp[0]] = QUrl::fromEncoded(temp[1].replace("+", " ").toLocal8Bit()).path();
		}
	}

	if (_path.contains("?"))
	{
		temp = _path.split("?");
		_path = temp[0];
		QString getData = temp[1];

		temp.clear();
		temp.push_back(getData);

		if (getData.contains("&"))
		{
			temp = getData.split("&");
		}

		QStringList temp2;
		for (auto& item : temp)
		{
			temp2 = item.split("=");
			_get[temp2[0]] = QUrl::fromEncoded(temp2[1].replace("+", " ").toLocal8Bit()).path();
		}
	}
}
