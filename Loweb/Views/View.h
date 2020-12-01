#pragma once
#include <QtCore>
#include "../Utils/Low-level/HttpRequest.h"
#include "../Utils/Low-level/HttpResponse.h"

class View
{
public:
	virtual HttpResponse Response(HttpRequest& request) = 0;
};