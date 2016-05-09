#include "GLWindow.h"
#include <QDebug>
#include <QString>
#include <QGuiApplication>
#include <QKeyEvent>

GLWindow::GLWindow()
{
}

GLWindow::~GLWindow(){
	makeCurrent();
	teardownGL();
}

void GLWindow::initializeGL(){
	initializeOpenGLFunctions();
	connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
	printContextInformation();

	glEnable(GL_MULTISAMPLE); // Enable MSAA
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	this->model = new Model(cubePath.toStdString());
}

void GLWindow::resizeGL(int width, int height){
	(void)width;
	(void)height;
}

void GLWindow::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	//TODO: Fix ASSERT error
	model->DrawModel();
}

void GLWindow::teardownGL(){
	qWarning() << "TEARING DOWN OPENGL";
	delete model;
	model = nullptr;
}

void GLWindow::keyPressEvent( QKeyEvent* e )
{
	switch ( e->key() )
	{
	case Qt::Key_Escape:
		QGuiApplication::instance()->quit();
		break;
	case Qt::Key_F1:
		this->update();
		break;
	default:
		QOpenGLWindow::keyPressEvent( e );
	}
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
