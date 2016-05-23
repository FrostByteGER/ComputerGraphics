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

	GLWindow window;
	window.setFormat(format);
	window.resize(800,600);

	#ifdef __MINGW32__
		window.setWindowTitle("MINGW x32");
	#endif

	#ifdef _MSC_VER
		#if _MSC_VER == 1900
			window.setWindowTitle("MSVC2015 x64");
		#define COMPILER_NAME
		#elif _MSC_VER == 1800
			window.setWindowTitle("MSVC2013 x64");
		#endif
	#endif

	#ifdef __ARM_ARCH_7A__
		window.setWindowTitle("ARMv7");
	#endif
	window.updateWindowTitle();
	window.show();
	return app.exec();
}
