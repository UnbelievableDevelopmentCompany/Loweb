#include "Model.h"

Loweb::Models::Model::Model()
{
}

void Loweb::Models::Model::SetTableName(const QString& tableName)
{
    _tableName = tableName;
}

QString Loweb::Models::Model::GetTableName()
{
    return _tableName;
}

void Loweb::Models::Model::AddData(DataTypes::Base* data)
{
    _data.push_back(data);
}
