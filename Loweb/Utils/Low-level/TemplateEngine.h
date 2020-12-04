#pragma once
#include <QtCore>
#include "../../dll/ExportDLL.h"

class TemplateEngine
{
public:
	EXPORTDLL TemplateEngine(const QString& data, const QMap<QString, QString>& context);
	EXPORTDLL QString ProcessData();
private:
	QString _data;
	QMap<QString, QString> _context;
};

