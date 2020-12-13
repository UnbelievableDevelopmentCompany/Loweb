#pragma once
#include <QtNetwork>
#include "DataTypes/Base.h"
#include "../dll/ExportDLL.h"

namespace Loweb::Models
{
	class Model
	{
	public:
		EXPORTDLL Model();
		EXPORTDLL void SetTableName(const QString& tableName);
		EXPORTDLL QString GetTableName();
		void AddData(DataTypes::Base* data);
	private:
		QString _tableName;
		QList<DataTypes::Base*> _data;
	};
}
