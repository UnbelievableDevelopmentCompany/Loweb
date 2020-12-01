#include "HttpResponse.h"

HttpResponse::HttpResponse(const QString& data, quint16 status, const QString& statusLine, const QString& contentType, const QString& charset)
	: _data(data), _status(status), _statusLine(statusLine), _contentType(contentType), _charset(charset)
{
}

QString HttpResponse::GenerateResponse()
{
	//response = "HTTP/1.1 404 Error\r\nContent-Type: text/html; charset=\"utf-8\"\r\n\r\nError 404!";
	
	QString response = "HTTP/1.1 ";
	response += QString::number(_status);
	response += " " + _statusLine;
	response += "\r\nContent-Type: " + _contentType;
	response += "; charset=\"" + _charset + "\"\r\n";

	if (!_contentLength.isEmpty())
		response += "Content-Length: " + _contentLength + "\r\n";
	if (!_date.isEmpty())
		response += "Date: " + _date + "\r\n";
	if (!_server.isEmpty())
		response += "Server: " + _server + "\r\n";
	if (!_connection.isEmpty())
		response += "Connection: " + _connection + "\r\n";

	response += "\r\n" + _data;
	return response;
}

HttpResponse& HttpResponse::SetData(const QString& data)
{
	_data = data;
	return *this;
}

HttpResponse& HttpResponse::SetStatus(quint16 status)
{
	_status = status;
	return *this;
}

HttpResponse& HttpResponse::SetStatusLine(const QString& statusLine)
{
	_statusLine = statusLine;
	return *this;
}

HttpResponse& HttpResponse::SetContentType(const QString& contentType)
{
	_contentType = contentType;
	return *this;
}

HttpResponse& HttpResponse::SetContentLength(const QString& contentLength)
{
	_contentLength = contentLength;
	return *this;
}

HttpResponse& HttpResponse::SetServer(const QString& server)
{
	_server = server;
	return *this;
}

HttpResponse& HttpResponse::SetConnection(const QString& connection)
{
	_connection = connection;
	return *this;
}

HttpResponse& HttpResponse::SetCharset(const QString& charset)
{
	_charset = charset;
	return *this;
}

HttpResponse& HttpResponse::SetDate(const QString& date)
{
	_date = date;
	return *this;
}
