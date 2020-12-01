#pragma once
#include <QtCore>
#include "../../dll/ExportDLL.h"

class HttpResponse
{
public:
	EXPORTDLL HttpResponse(const QString& data = "", quint16 status = 200, const QString& statusLine = "OK", const QString& contentType = "text/html", const QString& charset = "utf-8");
	EXPORTDLL QString GenerateResponse();
	EXPORTDLL HttpResponse& SetData(const QString& data);
	EXPORTDLL HttpResponse& SetStatus(quint16 status);
	EXPORTDLL HttpResponse& SetStatusLine(const QString& statusLine);
	EXPORTDLL HttpResponse& SetContentType(const QString& contentType);
	EXPORTDLL HttpResponse& SetContentLength(const QString& contentLength);
	EXPORTDLL HttpResponse& SetServer(const QString& server);
	EXPORTDLL HttpResponse& SetConnection(const QString& connection);
	EXPORTDLL HttpResponse& SetCharset(const QString& charset);
	EXPORTDLL HttpResponse& SetDate(const QString& date);
private:
	quint16 _status;
	QString _statusLine;
	QString _data;
	QString _contentType;
	QString _contentLength;
	QString _date;
	QString _server;
	QString _connection;
	QString _charset;
};

