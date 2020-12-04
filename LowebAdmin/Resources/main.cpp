#include "Config/{{ProjectName}}.h"
int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);
	{{ProjectName}} project;
	return app.exec();
}