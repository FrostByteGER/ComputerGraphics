#include "GLWindow.h"
#include <QDebug>
#include <QString>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QTime>
#include <cmath>

GLWindow::GLWindow()
{
	shader = new ShaderManager();
	timer.start();
}

GLWindow::~GLWindow(){
	makeCurrent();
	teardownGL();
}

void GLWindow::initializeGL(){
	initializeOpenGLFunctions();
	connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
	printContextInformation();

	glEnable(GL_MULTISAMPLE); // Enable MSAA
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	this->model = new Model(cubePath.toStdString(), shader);
	this->model2 = new Model(spherePath.toStdString(), shader);

	this->model->setLocation(0,0,-5);
	this->model2->setLocation(0,0,-5);
}

void GLWindow::resizeGL(int width, int height){
	projection.setToIdentity();
	projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void GLWindow::paintGL(){
	model->setLocation(std::sin(2.0f * 3.14f * 2.0f * static_cast<float>(timer.elapsed())), 0, -5);
	model->rotate(0,1,0);
	model2->rotate(0,-1,-1);
	glClear(GL_COLOR_BUFFER_BIT);
	auto shaders = shader->getShaderList();
	for(auto it = shaders.begin(); it != shaders.end(); ++it){
		it.value()->bind();
		auto meshes = shader->getMeshes(it.key());
		for(Mesh* mesh : meshes){
			mesh->DrawMesh(it.value());
		}
		it.value()->release();
	}
}

void GLWindow::teardownGL(){
	qWarning() << "TEARING DOWN OPENGL";
	delete model;
	model = nullptr;
	delete shader;
	shader = nullptr;
}

void GLWindow::update(){
	qWarning() << "UPDATING";
	QOpenGLWindow::update();
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
