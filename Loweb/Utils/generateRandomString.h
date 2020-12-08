#pragma once
#include <QtCore>
#include "../dll/ExportDLL.h"
#include "ConsoleTextStream.h"

EXPORTDLL QString generateRandomString(quint64 size = 15);