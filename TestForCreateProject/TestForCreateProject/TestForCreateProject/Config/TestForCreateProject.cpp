#include "TestForCreateProject.h"

TestForCreateProject::TestForCreateProject()
{
	Config("config.xml");
	server.StartServer();
}
