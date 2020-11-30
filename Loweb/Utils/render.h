#pragma once
#include <QtCore>
#include "Low-level/HttpRequestReader.h"

QString render(HttpRequestReader& request, const QString& templatePath, const QMap<QString, QString> context = {});