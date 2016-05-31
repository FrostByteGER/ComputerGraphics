#include <QGuiApplication>
#include "GLWindow.h"

int main(int argc, char *argv[])
{

	QGuiApplication app(argc,argv);
	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(3,3);
	format.setSamples(8); // 8x MSAA

	//TODO: Add Collision Tests here!

	GLWindow window;
	window.setFormat(format);
	window.resize(800,600);

	//Application Name
	const QString applicationName = "LabEngine";

	//Determine Compiler Type
	#ifdef __MINGW32__
		window.setWindowTitle(applicationName + "   " + "MINGW x32");
	#elif _MSC_VER
		#if _MSC_VER == 1900
			window.setWindowTitle(applicationName + "   " + "MSVC2015 x64");
		#elif _MSC_VER == 1800
			window.setWindowTitle(applicationName + "   " + "MSVC2013 x64");
		#endif
	#elif __ARM_ARCH_7A__
		window.setWindowTitle(applicationName + "   " + "ARMv7");
	#else
		window.setWindowTitle(applicationName + "   " + "UNKNOWN COMPILER");
	#endif
	window.updateWindowTitle();
	window.show();
	return app.exec();
}
