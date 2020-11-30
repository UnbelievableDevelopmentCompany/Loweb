#pragma once
#include <QtCore>
#include "Low-level/HttpRequestReader.h"
#include "../dll/ExportDLL.h"

EXPORTDLL QString render(HttpRequestReader& request, const QString& templatePath, const QMap<QString, QString> context = {});