#include <QApplication>
#include <QGLFormat>
#include "glwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLFormat glFormat;

    glFormat.setVersion(3,3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);


    GLWidget w(glFormat);
#ifdef __MINGW32__
	w.setWindowTitle("MINGW x32");
#endif
#ifdef _MSC_VER
#if _MSC_VER == 1900
	w.setWindowTitle("MSVC2015 x64");
#define COMPILER_NAME
#elif _MSC_VER == 1800
	w.setWindowTitle("MSVC2013 x64");
#endif
#endif
#ifdef __ARM_ARCH_7A__
	w.setWindowTitle("ARMv7");
#endif

    //Set 4:3 aspect ratio
    w.resize(800,600);
    //Move window to the center of the desktop-screen
    w.move(1920/2 - 800/2,1080/2 - 600/2);
    w.show();

    return a.exec();
}
