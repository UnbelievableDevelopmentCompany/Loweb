#include "Session.h"

Loweb::Utils::LowLevel::Session::Session(const QString& ip, const QMap<QString, QString>& data, const QDateTime& deletedTime)
	: _ip(ip), _deletedTime(deletedTime), _data(data)
{
}

const QString& Loweb::Utils::LowLevel::Session::GetIp() const
{
	return _ip;
}

const QMap<QString, QString>& Loweb::Utils::LowLevel::Session::GetData() const
{
	return _data;
}

QString Loweb::Utils::LowLevel::Session::GetData(const QString& name) const
{
	return _data[name];
}

const QDateTime& Loweb::Utils::LowLevel::Session::GetDeletedTime() const
{
	return _deletedTime;
}

bool Loweb::Utils::LowLevel::Session::isExpiration()
{
	return QDateTime::currentDateTime() > _deletedTime;
}

void Loweb::Utils::LowLevel::Session::AddData(const QString& name, const QString& data)
{
	_data[name] = data;
}
