#pragma once
#include <QtCore>
#include "../../dll/ExportDLL.h"
#include "HttpRequest.h"

namespace Loweb::Utils::LowLevel
{
	class TemplateEngine
	{
	public:
		EXPORTDLL TemplateEngine(const QString& data, const QMap<QString, QString>& context, const HttpRequest& httpRequest);
		EXPORTDLL QString ProcessData();
	private:
		QString _data;
		QMap<QString, QString> _context;
		HttpRequest _httpRequest;
	};
}