#include "render.h"

Loweb::Utils::LowLevel::HttpResponse Loweb::Utils::render(LowLevel::HttpRequest& request, const QString& templatePath, const QMap<QString, QString> context)
{
	QFile file(templatePath);
	file.open(QIODevice::ReadOnly);
	QString response = file.readAll();
	file.close();

	LowLevel::TemplateEngine templateEngine(response, context);
	response = templateEngine.ProcessData();

	return LowLevel::HttpResponse(response);
}