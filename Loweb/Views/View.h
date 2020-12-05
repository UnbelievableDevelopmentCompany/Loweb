#pragma once
#include <QtCore>
#include "../Utils/Low-level/HttpRequest.h"
#include "../Utils/Low-level/HttpResponse.h"

namespace Loweb::Views
{
	class View
	{
	public:
		virtual Utils::LowLevel::HttpResponse Response(Utils::LowLevel::HttpRequest& request) = 0;
	};
}