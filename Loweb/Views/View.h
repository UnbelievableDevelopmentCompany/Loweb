#pragma once
#include <QtCore>
#include "../Utils/Low-level/HttpRequestReader.h"

class View
{
public:
	virtual QString Response(HttpRequestReader & request) = 0;
};