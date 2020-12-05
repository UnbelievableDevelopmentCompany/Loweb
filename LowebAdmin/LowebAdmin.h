#pragma once
#include <QtCore>
#include "getEnv.h"

class LowebAdmin
{
public:
	LowebAdmin(int argc, char* argv[]);
	void Start();

	void WriteFileInFile(const QString& from, const QString& to, QMap<QString, QString> context);

	void CreateProjectVisualStudio(const QString& name, const QString& dir, const QString& lowebInclude, const QString& lowebLib, const QString& nameCompiller);

private:
	QStringList _argv;
	QStringList _flags;
};

