#include "LowebAdmin.h"

LowebAdmin::LowebAdmin(int argc, char* argv[])
{
	_argv.resize(argc);
	for (int i = 0; i < argc; ++i)
	{
		_argv[i] = argv[i];
	}
}

void LowebAdmin::Start()
{
	if (_argv[1] == "createproject" || _argv[1] == "cp")
	{
		if(_argv.size() >= 4)
			CreateProject(_argv[2], _argv[3]);
		else
			CreateProject(_argv[2]);
	}
}

void LowebAdmin::CreateProject(const QString& name, const QString& dir)
{
	QDir projectDir;
	projectDir.mkdir(dir + (dir.isEmpty() ? "" : "/") + name);
	QString projectPath = dir + (dir.isEmpty() ? "":"/") + name + "/";

	QTextStream ts;
	ts.setCodec("UTF-8");

	QFile target(projectPath + "main.cpp");
	QFile resource(":/createProject/Resources/main.cpp");
	target.open(QIODevice::WriteOnly);
	resource.open(QIODevice::ReadOnly);
	ts.setDevice(&target);
	ts << resource.readAll().replace("{{ProjectName}}", name.toLocal8Bit());
	target.close();
	resource.close();


	QDir().mkdir(projectPath + "Config");

	// Project.h
	target.setFileName(projectPath + "Config/" + name + ".h");
	resource.setFileName(":/createProject/Resources/Config/Project.h");
	target.open(QIODevice::WriteOnly);
	resource.open(QIODevice::ReadOnly);
	ts.setDevice(&target);
	ts << resource.readAll().replace("{{ProjectName}}", name.toLocal8Bit());
	target.close();
	resource.close();

	// Project.cpp
	target.setFileName(projectPath + "Config/" + name + ".cpp");
	resource.setFileName(":/createProject/Resources/Config/Project.cpp");
	target.open(QIODevice::WriteOnly);
	resource.open(QIODevice::ReadOnly);
	ts.setDevice(&target);
	ts << resource.readAll().replace("{{ProjectName}}", name.toLocal8Bit());
	target.close();
	resource.close();
}
