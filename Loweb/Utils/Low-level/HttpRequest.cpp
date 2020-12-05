#include "HttpRequest.h"

Loweb::Utils::LowLevel::HttpRequest::HttpRequest(const QString& httpRequest, bool isProccess)
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

void Loweb::Utils::LowLevel::HttpRequest::Proccess()
{
	QStringList lines = _httpRequest.split("\r\n");
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
}
