#pragma once
#include <QtCore>
#include "../dll/ExportDLL.h"

#include "../Views/View.h"

/// <summary>
/// В данном namespace хранятся классы, которые описывают приложение
/// </summary>
namespace Loweb::Apps
{
	/// <summary>
	/// Базовый класс, описывающий приложения
	/// </summary>
	class Application
	{
	public:
		/// <summary>
		/// Конструктор по умолчанию
		/// </summary>
		EXPORTDLL Application();


		/// <summary>
		/// Конструктор с инизиализацией указателя на родительское приложение
		/// </summary>
		/// <param name="parentApp">Указатель на родительское приложение</param>
		EXPORTDLL Application(Application* parentApp);


		/// <summary>
		/// Деструктор, который очищает все View, которые находились у него в массиве
		/// </summary>
		EXPORTDLL virtual ~Application();


		/// <summary>
		/// Добавление View в приложение
		/// </summary>
		/// <param name="path">Относительный url-путь</param>
		/// <param name="view">Указатель на саму View</param>
		EXPORTDLL void AddView(const QString& path, Views::View* view);


		/// <summary>
		/// Добавление дочернего приложения
		/// </summary>
		/// <param name="path">Относительный путь</param>
		/// <param name="app">Указатель на само приложение</param>
		EXPORTDLL void AddApplication(const QString& path, Application* app);


		/// <summary>
		/// Получение View по её относительному пути
		/// </summary>
		/// <param name="path">Относительный путь</param>
		/// <returns>Указатель на View</returns>
		EXPORTDLL Views::View* GetView(const QString& path);


		/// <summary>
		/// Получение дочернего приложения по относительному пути
		/// </summary>
		/// <param name="path">Относительный путь</param>
		/// <returns>Указатель на дочернее приложение</returns>
		EXPORTDLL Application* GetApplication(const QString& path);


		/// <summary>
		/// Получение словаря приложений
		/// </summary>
		/// <returns>Ссылка на словарь приложений</returns>
		EXPORTDLL QMap<QString, Application*>& GetApplications();


		/// <summary>
		/// Установка родительского приложения, при этом данное приложение не будет добавлено в массив родителя
		/// </summary>
		/// <param name="parentApp">Указатель на родительское приложение</param>
		EXPORTDLL void SetParentApp(Application* parentApp);
	private:
		QMap<QString, Views::View*> _views;
		QMap<QString, Application*> _apps;
		Application* _parentApp;
	};
}