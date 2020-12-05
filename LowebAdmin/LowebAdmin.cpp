#include "LowebAdmin.h"

LowebAdmin::LowebAdmin(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
	{
		if (argv[i][0] == '-')
			_flags.push_back(argv[i]);
		else
			_argv.push_back(argv[i]);
	}
}

void LowebAdmin::Start()
{
	if ((_argv[1] == "createproject" || _argv[1] == "cp"))
	{
		if (_flags.contains("-vs"))
		{
			if (_argv.size() >= 4)
			{
				QString projectName = _argv[2];
				QString projectDir = _argv[3];
				QString lowebInclude = QString(getEnv("LowebPath")) + "include";
				QString lowebLib = QString(getEnv("LowebPath")) + "lib/Loweb.lib";

				quint32 qtcompillerIndex;
				for (qtcompillerIndex = 0; qtcompillerIndex < _flags.size(); ++qtcompillerIndex)
				{
					if (_flags[qtcompillerIndex].startsWith("-qtcompiller_"))
					{
						break;
					}
					if (qtcompillerIndex == _flags.size() - 1)
						qtcompillerIndex = -2;
				}

				QString qtCompillerName = (qtcompillerIndex != -1 ? _flags[qtcompillerIndex].mid(13) : "msvc2019_64");
				CreateProjectVisualStudio(projectName, projectDir, lowebInclude, lowebLib, qtCompillerName);
			}

			else
			{
				QString projectName = _argv[2];
				QString projectDir = "";
				QString lowebInclude = QString(getEnv("LowebPath")) + "include";
				QString lowebLib = QString(getEnv("LowebPath")) + "lib\\Loweb.lib";

				quint32 qtcompillerIndex;
				for (qtcompillerIndex = 0; qtcompillerIndex < _flags.size(); ++qtcompillerIndex)
				{
					if (_flags[qtcompillerIndex].startsWith("-qtcompiller_"))
					{
						break;
					}
					if (qtcompillerIndex == _flags.size() - 1)
						qtcompillerIndex = -2;
				}

				QString qtCompillerName = (qtcompillerIndex != -1 ? _flags[qtcompillerIndex].mid(13) : "msvc2019_64");
				CreateProjectVisualStudio(projectName, projectDir, lowebInclude, lowebLib, qtCompillerName);
			}
		}
	}
}

void LowebAdmin::WriteFileInFile(const QString& from, const QString& to, QMap<QString, QString> context)
{
	QFile target(to);
	QFile resource(from);
	QTextStream ts(&target);
	ts.setCodec("UTF-8");
	target.open(QIODevice::WriteOnly);
	resource.open(QIODevice::ReadOnly);
	QByteArray result = resource.readAll();
	for (auto i = context.keyValueBegin(); i != context.keyValueEnd(); ++i)
	{
		result.replace(i.base().key(), i.base().value().toLocal8Bit());
	}
	ts << result;
	target.close();
	resource.close();
}

void LowebAdmin::CreateProjectVisualStudio(const QString& name, const QString& dir, const QString& lowebInclude, const QString& lowebLib, const QString& nameCompiller)
{
	QString projectPath = dir + (dir.isEmpty() ? "":"/") + name + "/";
	QDir().mkdir(projectPath);
	QDir().mkdir(projectPath + name);
	QDir().mkdir(projectPath + name + "/Config");


	// main.cpp
	WriteFileInFile(":/createProject/Resources/main.cpp", projectPath + name + "/main.cpp", { {"{{ProjectName}}", name} });


	// <projectname>.sln
	WriteFileInFile(":/createProject/Resources/TestForCreateProject.sln", projectPath + name + ".sln", { {"{{ProjectName}}", name} });
	

	// <projectname>.vcxproj
	WriteFileInFile(":/createProject/Resources/TestForCreateProject.vcxproj", projectPath + name + "/" + name + ".vcxproj", {
		{"{{ProjectName}}", name},
		{"{{LowebInclude}}", lowebInclude},
		{"{{LowebLib}}", lowebLib},
		{"{{NameCompiller}}", nameCompiller}
	});


	// <projectname>.vcxproj.filters
	WriteFileInFile(":/createProject/Resources/TestForCreateProject.vcxproj.filters", projectPath + name + "/" + name + ".vcxproj.filters", { {"{{ProjectName}}", name} });


	// <projectname>.vcxproj.user
	WriteFileInFile(":/createProject/Resources/TestForCreateProject.vcxproj.user", projectPath + name + "/" + name + ".vcxproj.user", {});


	// Project.h
	WriteFileInFile(":/createProject/Resources/Config/Project.h", projectPath + name + "/Config/" + name + ".h", { {"{{ProjectName}}", name} });


	// Project.cpp
	WriteFileInFile(":/createProject/Resources/Config/Project.cpp", projectPath + name + "/Config/" + name + ".cpp", { {"{{ProjectName}}", name} });

}
