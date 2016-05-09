#include "GLWindow.h"
#include <QDebug>
#include <QString>

GLWindow::GLWindow()
{

}

GLWindow::~GLWindow(){
	makeCurrent();
	teardownGL();
}

void GLWindow::initializeGL(){
	initializeOpenGLFunctions();
	printContextInformation();

	glEnable(GL_MULTISAMPLE); // Enable MSAA
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void GLWindow::resizeGL(int width, int height){
	(void)width;
	(void)height;
}

void GLWindow::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
}

void GLWindow::teardownGL(){

}

void GLWindow::printContextInformation(){
	QString glType;
	QString glVersion;
	QString glProfile;

	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break;
	switch(format().profile()){
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
