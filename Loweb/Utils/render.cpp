#include "render.h"

HttpResponse render(HttpRequest& request, const QString& templatePath, const QMap<QString, QString> context)
{
	QFile file(templatePath);
	file.open(QIODevice::ReadOnly);
	QString response = file.readAll();
	file.close();
	return HttpResponse(response);
}