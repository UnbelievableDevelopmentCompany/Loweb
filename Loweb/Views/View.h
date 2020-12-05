#pragma once
#include <QtCore>
#include "../Utils/Low-level/HttpRequest.h"
#include "../Utils/Low-level/HttpResponse.h"

namespace Loweb::Views
{
	class View
	{
	public:

		EXPORTDLL View(const QString& response);
		EXPORTDLL View();

		EXPORTDLL virtual Utils::LowLevel::HttpResponse Response(Utils::LowLevel::HttpRequest& request);

		EXPORTDLL virtual Utils::LowLevel::HttpResponse Get(Utils::LowLevel::HttpRequest& request);

		EXPORTDLL virtual Utils::LowLevel::HttpResponse Post(Utils::LowLevel::HttpRequest& request);
	protected:
		QString _response;
	};
}