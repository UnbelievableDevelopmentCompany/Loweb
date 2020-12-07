#pragma once
#include <QtCore>
#include "../Utils/Low-level/HttpRequest.h"
#include "../Utils/Low-level/HttpResponse.h"
#include "../Apps/Application.h"


namespace Loweb::Views
{
	class View
	{
	public:

		EXPORTDLL View(const QString& response, Loweb::Apps::Application* parentApp = nullptr);
		EXPORTDLL View(Loweb::Apps::Application* parentApp);
		EXPORTDLL View();

		EXPORTDLL virtual Utils::LowLevel::HttpResponse Response(Utils::LowLevel::HttpRequest& request);

		EXPORTDLL virtual Utils::LowLevel::HttpResponse Get(Utils::LowLevel::HttpRequest& request);

		EXPORTDLL virtual Utils::LowLevel::HttpResponse Post(Utils::LowLevel::HttpRequest& request);

		EXPORTDLL void SetParentApp(Loweb::Apps::Application* parentApp);
	protected:
		QString _response;

	private:
		Loweb::Apps::Application* _parentApp;
	};
}