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
    //Set 4:3 aspect ratio
    w.resize(800,600);
    //Move window to the center of the desktop-screen
    w.move(1920/2 - 800/2,1080/2 - 600/2);
    w.show();

    return a.exec();
}
