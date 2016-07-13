#include <QApplication>
#include <QString>
#include "MainWindow.h"
#include "GLWidget.h"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	MainWindow mainWindow;

	//Application Name
	const QString applicationName = "Minigolf | LabEngine";

	//Determine Compiler Type
#ifdef __MINGW32__
	mainWindow.setWindowTitle(applicationName + "   " + "MINGW x32");
#elif _MSC_VER
#if _MSC_VER == 1900
	mainWindow.setWindowTitle(applicationName + "   " + "MSVC2015 x64");
#elif _MSC_VER == 1800
	mainWindow.setWindowTitle(applicationName + "   " + "MSVC2013 x64");
#endif
#elif __ARM_ARCH_7A__
	mainWindow.setWindowTitle(applicationName + "   " + "ARMv7");
#else
	mainWindow.setWindowTitle(applicationName + "   " + "UNKNOWN COMPILER");
#endif
	//window.show();
	mainWindow.show();
	return app.exec();
}
