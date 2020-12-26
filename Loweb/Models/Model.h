#pragma once
#include <QtNetwork>
#include "DataTypes/Base.h"
#include "../dll/ExportDLL.h"


/// <summary>
/// ¬ данном namespace хран€тс€ классы св€занные с модел€ми
/// </summary>
namespace Loweb::Models
{
	class Model
	{
	public:
		EXPORTDLL Model();
		EXPORTDLL void SetTableName(const QString& tableName);
		EXPORTDLL QString GetTableName();
		EXPORTDLL void AddData(DataTypes::Base* data);

		static inline QString _tableName = "";
		static inline QList<DataTypes::Base*> _data = {};

	private:
		QList<QVariant> _values;
	};
}
