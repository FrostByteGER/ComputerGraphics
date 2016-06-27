#include <QGuiApplication>
#include <QString>
#include "ui_MainWindow.h"
#include "GLWidget.h"

int main(int argc, char *argv[])
{

	// OpenGL Version
	const int OPENGL_MAJOR_VERSION       = 4;
	const int OPENGL_MINOR_VERSION       = 3;

	// OpenGL Buffer Sizes
	const int OPENGL_DEPTH_BUFFER_SIZE   = 24;
	const int OPENGL_STENCIL_BUFFER_SIZE = 8;
	const int OPENGL_RED_BUFFER_SIZE     = 8;
	const int OPENGL_GREEN_BUFFER_SIZE   = 8;
	const int OPENGL_BLUE_BUFFER_SIZE    = 8;
	const int OPENGL_ALPHA_BUFFER_SIZE   = -1;
	const int OPENGL_MSAA_COUNT          = 8;

	QApplication app(argc,argv);
	QSurfaceFormat format;

	// Set all required Information
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION);
	format.setSamples(OPENGL_MSAA_COUNT); // 8x MSAA
	format.setDepthBufferSize(OPENGL_DEPTH_BUFFER_SIZE);
	format.setStencilBufferSize(OPENGL_STENCIL_BUFFER_SIZE);
	format.setRedBufferSize(OPENGL_RED_BUFFER_SIZE);
	format.setGreenBufferSize(OPENGL_GREEN_BUFFER_SIZE);
	format.setBlueBufferSize(OPENGL_BLUE_BUFFER_SIZE);
	format.setAlphaBufferSize(OPENGL_ALPHA_BUFFER_SIZE);


	Ui::MainWindow ui;
	QMainWindow* mainWindow = new QMainWindow();
	ui.setupUi(mainWindow);

	ui.renderWidget->setFormat(format);
	//Application Name
	const QString applicationName = "LabEngine";

	//Determine Compiler Type
#ifdef __MINGW32__
	mainWindow->setWindowTitle(applicationName + "   " + "MINGW x32");
#elif _MSC_VER
#if _MSC_VER == 1900
	mainWindow->setWindowTitle(applicationName + "   " + "MSVC2015 x64");
#elif _MSC_VER == 1800
	mainWindow->setWindowTitle(applicationName + "   " + "MSVC2013 x64");
#endif
#elif __ARM_ARCH_7A__
	mainWindow->setWindowTitle(applicationName + "   " + "ARMv7");
#else
	mainWindow->setWindowTitle(applicationName + "   " + "UNKNOWN COMPILER");
#endif

	//mainWindow.updateWindowTitle();

	qWarning() << "### BUFFER SIZE INFORMATION ###";
	qWarning() << qPrintable("Depth Buffer:   " + QString::number(format.depthBufferSize()));
	qWarning() << qPrintable("Stencil Buffer: " + QString::number(format.stencilBufferSize()));
	qWarning() << qPrintable("Red Buffer:     " + QString::number(format.redBufferSize()));
	qWarning() << qPrintable("Green Buffer:   " + QString::number(format.greenBufferSize()));
	qWarning() << qPrintable("Blue Buffer:    " + QString::number(format.blueBufferSize()));
	qWarning() << qPrintable("Alpha Buffer:   " + QString::number(format.alphaBufferSize()));
	qWarning() << "### END ###";

	//window.show();
	mainWindow->show();
	return app.exec();
}
