#pragma once
#include <QtCore>
#include "../../dll/ExportDLL.h"

namespace Loweb::Utils::LowLevel
{
	class Session
	{
	public:
		EXPORTDLL Session(const QString& ip = "", const QMap<QString, QString>& data = {}, const QDateTime& deletedTime = QDateTime::currentDateTime().addSecs(15 * 60));

		EXPORTDLL const QString& GetIp() const;
		EXPORTDLL const QMap<QString, QString>& GetData() const;
		EXPORTDLL QString GetData(const QString& name) const;
		EXPORTDLL const QDateTime& GetDeletedTime() const;

		EXPORTDLL bool isExpiration();

		EXPORTDLL void AddData(const QString& name, const QString& data);
	private:
		QString _ip;
		QMap<QString, QString> _data;
		QDateTime _deletedTime;
	};
}