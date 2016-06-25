#include "GLWindow.h"
#include <QDebug>
#include <QString>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <QPair>
#include <cmath>
#include <QOpenGLFunctions_4_3_Core>
#include "InputManager.h"

GLWindow::GLWindow()
{
	directionalLight.transform.setTranslation(0,10,5);
	directionalLight.lightColor.setRgb(255,255,255);
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
	physicsSimulation.quit();
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
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, renderType);
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	this->model = new Model(cubePath.toStdString(), shader);
	this->model2 = new Model(spherePath.toStdString(), shader);
	this->model3 = new Model(customPath.toStdString(), shader);

	this->model->setLocation(0,0,-5);
	this->model2->setLocation(1,0,-5);
	this->model3->setLocation(7,-10,-10);

	this->model->setModelColor(QColor(255,0,0,255));
	this->model2->setModelColor(QColor(0,255,0,255));
	this->model3->setModelColor(QColor(0,0,255,255));



	//TODO: Write custom class that wraps around this with simple integers
	//TODO2: move to main again with thread synchronization and wait for completion of initializeGL
	auto version = context()->versionFunctions<QOpenGLFunctions_4_3_Core>();
	if(!version){
		qFatal(QString("FATAL ERROR: OPENGL VERSION INSUFFICIENT. REQUIRED: " + QString::number(format().version().first) + "." + QString::number(format().version().second)).toStdString().c_str());
		QCoreApplication::exit(-1);
	}
}

void GLWindow::resizeGL(int width, int height){
	projection.setToIdentity();
	projection.perspective(45.0f, float(width) / float(height), 0.01f, 1000.0f);
}

void GLWindow::paintGL(){

	auto startTime = std::chrono::high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(updateRenderType){
		glPolygonMode(GL_FRONT_AND_BACK, renderType);
		updateRenderType = false;
	}
	auto shaders = shader->getShaderList();
	for(auto currentShader : shaders){
		currentShader->bind();
		//currentShader->setUniformValue("lightPosition", directionalLight.transform.translation());
		currentShader->setAttributeValue("lightPosition", directionalLight.transform.translation());
		currentShader->setUniformValue("lightColor", directionalLight.lightColor);
		worldToCamera = currentShader->uniformLocation("worldToCamera");
		cameraToProjection = currentShader->uniformLocation("cameraToProjection");
		currentShader->setUniformValue(worldToCamera, camera.toMatrix());
		currentShader->setUniformValue(cameraToProjection, projection);
		auto meshes = currentShader->getMeshes();
		for(auto mesh : meshes){
			mesh->DrawMesh(currentShader);
		}
		currentShader->release();
	}




//	for(auto it = shaders.begin(); it != shaders.end(); ++it){
//		auto currentShader = it.
//		currentShader->bind();
//		worldToCamera = currentShader->uniformLocation("worldToCamera");
//		cameraToView = currentShader->uniformLocation("cameraToView");
//		currentShader->setUniformValue(worldToCamera, camera.toMatrix());
//		currentShader->setUniformValue(cameraToView, projection);
//		auto meshes = shader->getMeshes(it.key());
//		for(Mesh* mesh : meshes){
//			mesh->DrawMesh(currentShader);
//		}
//		currentShader->release();
//	}
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
	delete model3;
	model3 = nullptr;
	delete shader;
	shader = nullptr;
}

void GLWindow::update(){
	//qWarning() << "UPDATING";

	model->rotate(0,1,0);
	model2->rotate(0,-1,-1);

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
	if(InputManager::keyPressed(Qt::Key_F2)){
		directionalLight.transform.translate(0,-1,0);
	}
	if(InputManager::keyPressed(Qt::Key_F3)){
		directionalLight.transform.translate(0,1,0);
	}

	if(InputManager::keyTriggered(Qt::Key_F5)){
		qDebug() << ">>>STARTING PHYSICS-SIMULATION<<<";
		physicsSimulation.start();
	}

	if(InputManager::keyTriggered(Qt::Key_F6)){
		qDebug() << ">>>PAUSING/RESUMING PHYSICS-SIMULATION<<<";
		physicsSimulation.TogglePause();
	}

	if(InputManager::keyTriggered(Qt::Key_F7)){
		qDebug() << ">>>STOPPING PHYSICS-SIMULATION<<<";
		physicsSimulation.quit();
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
    setTitle(windowTitle + "    Frame-Time: " + QString::number(deltaTimeMS, 'g', 2) + "ms" + "    FPS: " + QString::number(1000.0 / deltaTimeMS));
}
