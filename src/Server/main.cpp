#include <QtCore/QTextCodec>
#include <QtCore/QCoreApplication>

#include "Server.h"

int main (int argc, char **argv)
{
	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));
	QTextCodec::setCodecForLocale (QTextCodec::codecForName ("UTF-8"));

	QCoreApplication app (argc, argv);

	Core::Server server;

	return server.listen () ? app.exec() : 1;
}
