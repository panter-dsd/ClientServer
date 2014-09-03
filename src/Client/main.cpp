#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QDebug>

#include <QtGui/QApplication>

#include "MainWindow.h"

int main (int argc, char **argv)
{
	QTextCodec::setCodecForCStrings (QTextCodec::codecForName ("UTF-8"));
	QTextCodec::setCodecForLocale (QTextCodec::codecForName ("UTF-8"));

	QApplication app (argc, argv);

	app.setQuitOnLastWindowClosed (true);

	Gui::MainWindow window;
	window.show ();

	return app.exec();
}
