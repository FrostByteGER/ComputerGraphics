#include "GLWindow.h"
#include <QDebug>
#include <QString>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <cmath>
#include "InputManager.h"
#include "Definitions.h"

GLWindow::GLWindow()
{
	deltaTimeNS = 0.0;
	deltaTimeMS = 0.0;
	windowUpdateTime = 100;
	shader = new ShaderManager();
	windowUpdateTimer = new QTimer();
	updateRenderType = false;
	renderType = GL_LINE;
}

GLWindow::~GLWindow(){
	makeCurrent();
	teardownGL();
	windowUpdateTimer->stop();
	delete windowUpdateTimer;
	windowUpdateTimer = nullptr;
}

void GLWindow::initializeGL(){
	initializeOpenGLFunctions();
	connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
	connect(windowUpdateTimer, SIGNAL(timeout()), this, SLOT(updateWindowTitle()));
	windowUpdateTimer->start(windowUpdateTime);
	printContextInformation();

	glEnable(GL_MULTISAMPLE); // Enable MSAA
	glPolygonMode(GL_FRONT_AND_BACK, renderType);
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	this->model = new Model(cubePath.toStdString(), shader);
	this->model2 = new Model(spherePath.toStdString(), shader);
	this->model3 = new Model(customPath.toStdString(), shader);

	this->model->setLocation(0,0,-5);
	this->model2->setLocation(0,0,-5);
	this->model3->setLocation(7,-10,-10);
}

void GLWindow::resizeGL(int width, int height){
	projection.setToIdentity();
	projection.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void GLWindow::paintGL(){
	auto startTime = std::chrono::high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT);
	if(updateRenderType){
		glPolygonMode(GL_FRONT_AND_BACK, renderType);
		updateRenderType = false;
	}
	auto shaders = shader->getShaderList();
	for(auto it = shaders.begin(); it != shaders.end(); ++it){
		auto currentShader = it.value();
		currentShader->bind();
		worldToCamera = currentShader->uniformLocation("worldToCamera");
		cameraToView = currentShader->uniformLocation("cameraToView");
		currentShader->setUniformValue(worldToCamera, camera.toMatrix());
		currentShader->setUniformValue(cameraToView, projection);
		auto meshes = shader->getMeshes(it.key());
		for(Mesh* mesh : meshes){
			mesh->DrawMesh(currentShader);
		}
		currentShader->release();
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = endTime - startTime;
	deltaTimeNS = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();
	deltaTimeMS = deltaTimeNS / 1000000.0;
}

void GLWindow::teardownGL(){
	qWarning() << "TEARING DOWN OPENGL";
	delete model;
	model = nullptr;
	delete model2;
	model2 = nullptr;
	delete shader;
	shader = nullptr;
}

void GLWindow::update(){
#ifdef LAB_ENGINE_DEBUG
	qWarning() << "UPDATING";
#endif

	//model->setLocation(std::sin(2.0f * 3.14f * 2.0f * static_cast<float>(timer.elapsed())), 0, -5);
	//model->rotate(0,1,0);
	//model2->rotate(0,-1,-1);

	InputManager::update();


	if(InputManager::keyTriggered(Qt::Key_Escape)){
		qWarning() << "CLOSING APPLICATION!";
		QGuiApplication::instance()->quit();
	}
	if(InputManager::keyTriggered(Qt::Key_F1)){
		if(renderType == GL_LINE){
			qWarning() << "FILL MODE";
			renderType = GL_FILL;
		}else if(renderType == GL_FILL){
			qWarning() << "LINE MODE";
			renderType = GL_LINE;
		}else{
			qWarning() << "LINE MODE";
			renderType = GL_LINE;
		}
		updateRenderType = true;
	}

	// Camera Transformation
	if (InputManager::buttonPressed(Qt::RightButton))
	{
		static const float transSpeed = 0.25f;
		static const float rotSpeed   = 0.25f;

		// Handle rotations
		camera.rotate(-rotSpeed * InputManager::mouseDelta().x(), Camera::LocalUp);
		camera.rotate(-rotSpeed * InputManager::mouseDelta().y(), camera.right());

		// Handle translations
		QVector3D translation;
		if (InputManager::keyPressed(Qt::Key_W))
		{
			translation += camera.forward();
		}
		if (InputManager::keyPressed(Qt::Key_S))
		{
			translation -= camera.forward();
		}
		if (InputManager::keyPressed(Qt::Key_A))
		{
			translation -= camera.right();
		}
		if (InputManager::keyPressed(Qt::Key_D))
		{
			translation += camera.right();
		}
		if (InputManager::keyPressed(Qt::Key_Q))
		{
			translation -= camera.up();
		}
		if (InputManager::keyPressed(Qt::Key_E))
		{
			translation += camera.up();
		}
		camera.translate(transSpeed * translation);
	}

	QOpenGLWindow::update();
}

void GLWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		event->ignore();
	}
	else
	{
		InputManager::registerKeyPress(event->key());
	}
}

void GLWindow::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		event->ignore();
	}
	else
	{
		InputManager::registerKeyRelease(event->key());
	}
}

void GLWindow::mousePressEvent(QMouseEvent* event)
{
	qWarning() << "MOUSE PRESS EVENT";
	InputManager::registerMousePress(event->button());
}

void GLWindow::mouseReleaseEvent(QMouseEvent* event)
{
	InputManager::registerMouseRelease(event->button());
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

void GLWindow::setWindowTitle(const QString& title)
{
	windowTitle = title;
}

void GLWindow::updateWindowTitle()
{
	setTitle(windowTitle + "    Frame-Time: " + QString::number(deltaTimeMS, 'g', 2) + "ms");
}
