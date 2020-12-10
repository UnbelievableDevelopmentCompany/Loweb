#pragma once
#include <QtCore>
#include "../dll/ExportDLL.h"
#include "ConsoleTextStream.h"

namespace Loweb::Utils
{
	EXPORTDLL QString generateRandomCSRFToken(quint64 size = 15);
}