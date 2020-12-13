#include "TemplateEngine.h"
#include "Server.h"

Loweb::Utils::LowLevel::TemplateEngine::TemplateEngine(const QString& data, const QMap<QString, QString>& context, const Loweb::Utils::LowLevel::HttpRequest& httpRequest)
	:_data(data), _context(context), _httpRequest(httpRequest)
{
	_context[_httpRequest.GetServer()->GetConfig()->nameCSRFToken] = _httpRequest.GetSession()->GetData(_httpRequest.GetServer()->GetConfig()->nameCSRFToken);
}

QString Loweb::Utils::LowLevel::TemplateEngine::ProcessData()
{
	QString result = _data;
	for (auto i = _context.keyValueBegin(); i != _context.keyValueEnd(); ++i)
	{
		QString key = i.base().key();
		QString value = i.base().value();
		result.replace("{{" + key + "}}", value);
	}
	return result;
}
