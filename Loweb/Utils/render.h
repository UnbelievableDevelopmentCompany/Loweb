﻿#pragma once
#include <QtCore>
#include "Low-level/HttpRequest.h"
#include "Low-level/HttpResponse.h"
#include "../dll/ExportDLL.h"

EXPORTDLL HttpResponse render(HttpRequest& request, const QString& templatePath, const QMap<QString, QString> context = {});