#include "{{ProjectName}}.h"

{{ProjectName}}::{{ProjectName}}()
{
	Config("config.xml");
	server.StartServer();
}