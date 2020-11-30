#include "HttpRequestReader.h"

HttpRequestReader::HttpRequestReader(const QString& httpRequest, bool isProccess)
{
	_httpRequest = httpRequest;
	if (isProccess)
		Proccess();
}

QString HttpRequestReader::GetPath()
{
	return _path;
}

QString HttpRequestReader::GetMethod()
{
	return _method;
}

QString HttpRequestReader::GetVariable(const QString& varname)
{
	return _variables[varname];
}

void HttpRequestReader::Proccess()
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
