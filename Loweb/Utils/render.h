#pragma once
#include <QtCore>
#include "Low-level/HttpRequest.h"
#include "Low-level/HttpResponse.h"
#include "../dll/ExportDLL.h"
#include "Low-level/TemplateEngine.h"

namespace Loweb::Utils
{
	EXPORTDLL LowLevel::HttpResponse render(LowLevel::HttpRequest& request, const QString& templatePath, const QMap<QString, QString> context = {});
}