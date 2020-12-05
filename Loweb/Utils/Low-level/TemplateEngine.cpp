#include "TemplateEngine.h"

Loweb::Utils::LowLevel::TemplateEngine::TemplateEngine(const QString& data, const QMap<QString, QString>& context)
	:_data(data), _context(context)
{
}

QString Loweb::Utils::LowLevel::TemplateEngine::ProcessData()
{
	QString result = _data;
	for (auto i = _context.keyValueBegin(); i != _context.keyValueEnd(); ++i)
	{
		result.replace("{{" + i.base().key() + "}}", i.base().value());
	}
	return result;
}
