#pragma once
#include <QtCore>

class LowebAdmin
{
public:
	LowebAdmin(int argc, char* argv[]);
	void Start();

	void CreateProject(const QString& name, const QString& dir = "");

private:
	QVector<QString> _argv;
};

