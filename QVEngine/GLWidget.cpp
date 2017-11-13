#include "GLWidget.h"
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <QPair>
#include <cmath>
#include <QOpenGLFunctions_4_3_Core>
#include "InputManager.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
	directionalLight.transform.setTranslation(0,10,5);
	directionalLight.lightColor.setRgb(255,255,255);
	windowUpdateTime = 100;
	shader = new ShaderManager();
	windowUpdateTimer = new QTimer();
	updateRenderType = false;
	renderType = GL_LINE;
	derp = 0.0f;
}

GLWidget::~GLWidget(){
	makeCurrent();
	teardownGL();
	windowUpdateTimer->stop();
	delete windowUpdateTimer;
	windowUpdateTimer = nullptr;
}

void GLWidget::initializeGL(){
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


	Model* box = new Model(cubePath.toStdString(), shader);
	Model* box2 = new Model(cubePath.toStdString(), shader);
	Model* box3 = new Model(cubePath.toStdString(), shader);
	Model* winBox = new Model(cubePath.toStdString(), shader);
	Model* sphere1 = new Model(spherePath.toStdString(), shader);
	Model* playerSphere = new Model(spherePath.toStdString(), shader);
	Model* arena = new Model(floorPath.toStdString(), shader);

	playerSphere->setLocation(20,1.0,0);
	box->setLocation(10,1,5);
	box2->setLocation(1,1,9);
	box3->setLocation(4,1,1);
	winBox->setLocation(-20,1.0,0);
	sphere1->setLocation(1,1,-5);
	arena->setLocation(0,-1,0);

	box->setModelColor(QColor(255,0,0,255));
	winBox->setModelColor(QColor(255,215,0));
	winBox->setForceColorOnly(true);
	sphere1->setModelColor(QColor(0,255,0,255));
	playerSphere->setModelColor(QColor(0,255,255,255));
	arena->setModelColor(QColor(255,255,255));


	models.append(playerSphere);
	models.append(box);
	models.append(box2);
	models.append(box3);
	models.append(sphere1);
	models.append(arena);
	models.append(winBox);




	//TODO: Write custom class that wraps around this with simple integers
	//TODO2: move to main again with thread synchronization and wait for completion of initializeGL
	auto version = context()->versionFunctions<QOpenGLFunctions_4_3_Core>();
	if(!version){
		qFatal(QString("FATAL ERROR: OPENGL VERSION INSUFFICIENT. REQUIRED: " + QString::number(format().version().first) + "." + QString::number(format().version().second)).toStdString().c_str());
		QCoreApplication::exit(-1);
	}

	emit updateModels();
}

void GLWidget::resizeGL(int width, int height){
	projection.setToIdentity();
	projection.perspective(45.0f, float(width) / float(height), 0.01f, 1000.0f);
}

void GLWidget::paintGL(){

	qDebug() << clock.GetFrameDelta();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(updateRenderType){
		glPolygonMode(GL_FRONT_AND_BACK, renderType);
		updateRenderType = false;
	}
	auto shaders = shader->getShaderList();
	for(auto currentShader : shaders){
		currentShader->bind();
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
	derp += 1.0f;
	//qDebug() << derp;
	if(derp >= 250.0f){
		//qDebug() << "ADDDDDDING MODEL!!!";
		//models.append(new Model(customPath.toStdString(), shader));
		derp = 0.0f;
		//emit updateModels();
	}
}

void GLWidget::teardownGL(){
	qWarning() << "TEARING DOWN OPENGL";
}

void GLWidget::update(){
	InputManager::update();

	if(InputManager::keyTriggered(Qt::Key_Escape)){
		qWarning() << "CLOSING APPLICATION!";
		QApplication::instance()->quit();
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

	QOpenGLWidget::update();
}

void GLWidget::keyPressEvent(QKeyEvent* event)
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

void GLWidget::keyReleaseEvent(QKeyEvent* event)
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

void GLWidget::mousePressEvent(QMouseEvent* event)
{
	qWarning() << "MOUSE PRESS EVENT";
	InputManager::registerMousePress(event->button());
}

void GLWidget::mouseReleaseEvent(QMouseEvent* event)
{
	InputManager::registerMouseRelease(event->button());
}

void GLWidget::printContextInformation(){
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

void GLWidget::setWindowTitle(const QString& title)
{
	windowTitle = title;
}

void GLWidget::updateWindowTitle()
{
	//setTitle(windowTitle + "    Frame-Time: " + QString::number(deltaTimeMS, 'g', 2) + "ms" + "    FPS: " + QString::number(1000.0 / deltaTimeMS));
}
