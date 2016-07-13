#include "GLWidget.h"
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <QPair>
#include <cmath>
#include <QOpenGLFunctions_3_3_Core>
#include "InputManager.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
	directionalLight.transform.setTranslation(0,10,5);
	directionalLight.lightColor.setRgb(255,255,255);
	windowUpdateTime = 100;
	shader = new ShaderManager();
	windowUpdateTimer = new QTimer();
	updateRenderType = false;
	renderType = GL_FILL;
	camera.setTranslation(35,20,20);
	camera.rotate(-30.0f,1,0,0);
	camera.rotate(60.0f,0,1,0);
}

GLWidget::~GLWidget(){
	makeCurrent();
	teardownGL();
	physicsSimulation.quit();
	physicsSimulation.wait();
	windowUpdateTimer->stop();
	delete windowUpdateTimer;
	windowUpdateTimer = nullptr;
}
void GLWidget::initializeScene(){
	Model* box = new Model(cubePath.toStdString(), "Static Obstacle", shader, &physicsSimulation, COLLISION_BOX, MODEL_BOX);
	Model* box2 = new Model(cubePath.toStdString(), "Static Obstacle", shader, &physicsSimulation, COLLISION_BOX, MODEL_BOX);
	Model* box3 = new Model(cubePath.toStdString(), "Static Obstacle", shader, &physicsSimulation, COLLISION_BOX, MODEL_BOX);
	Model* winBox = new Model(cubePath.toStdString(), "Target", shader, &physicsSimulation, COLLISION_BOX, MODEL_BOX);
	Model* sphere1 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE, MODEL_SPHERE);
	Model* playerSphere = new Model(spherePath.toStdString(), "Player Sphere", shader, &physicsSimulation, COLLISION_SPHERE, MODEL_SPHERE);
	Model* arena = new Model(floorPath.toStdString(), "Arena", shader, &physicsSimulation, COLLISION_BOX, MODEL_FLOOR);

	playerSphere->setColliderID(1);
	winBox->setColliderID(2);

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
	physicsSimulation.registerPhysicsBox(static_cast<PhysicsBox*>(box->getCollider()));
	physicsSimulation.registerPhysicsBox(static_cast<PhysicsBox*>(box2->getCollider()));
	physicsSimulation.registerPhysicsBox(static_cast<PhysicsBox*>(box3->getCollider()));
	physicsSimulation.registerPhysicsBox(static_cast<PhysicsBox*>(winBox->getCollider()));
	physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere1->getCollider()));
	physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(playerSphere->getCollider()));

	models.append(playerSphere);
	models.append(winBox);
	models.append(arena);
	models.append(box);
	models.append(box2);
	models.append(box3);
	models.append(sphere1);

	{
		Model* sphere12 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere12->setLocation(-8,1, -1);
		sphere12->setForceColorOnly(true);
		sphere12->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere12->getCollider()));
		models.append(sphere12);

		Model* sphere13 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere13->setLocation(-8,1, 1);
		sphere13->setForceColorOnly(true);
		sphere13->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere13->getCollider()));
		models.append(sphere13);

		Model* sphere14 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere14->setLocation(-8,1, 3);
		sphere14->setForceColorOnly(true);
		sphere14->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere14->getCollider()));
		models.append(sphere14);

		Model* sphere15 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere15->setLocation(-6,1, 3);
		sphere15->setForceColorOnly(true);
		sphere15->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere15->getCollider()));
		models.append(sphere15);

		Model* sphere16 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere16->setLocation(-4,1, 3);
		sphere16->setForceColorOnly(true);
		sphere16->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere16->getCollider()));
		models.append(sphere16);

		Model* sphere8 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere8->setLocation(-4,1, -1);
		sphere8->setForceColorOnly(true);
		sphere8->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere8->getCollider()));
		models.append(sphere8);

		Model* sphere9 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere9->setLocation(-6,1, -1);
		sphere9->setForceColorOnly(true);
		sphere9->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere9->getCollider()));
		models.append(sphere9);

		Model* sphere10 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere10->setLocation(-4,1, 1);
		sphere10->setForceColorOnly(true);
		sphere10->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere10->getCollider()));
		models.append(sphere10);

		Model* sphere11 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere11->setLocation(-6,1, 1);
		sphere11->setForceColorOnly(true);
		sphere11->setModelColor(QColor(255,0,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere11->getCollider()));
		models.append(sphere11);

		Model* sphere = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere->setLocation(-5,17, 0);
		sphere->setForceColorOnly(true);
		sphere->setModelColor(QColor(255,165,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere->getCollider()));
		models.append(sphere);

		Model* sphere4 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere4->setLocation(-7,17, 0);
		sphere4->setForceColorOnly(true);
		sphere4->setModelColor(QColor(255,165,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere4->getCollider()));
		models.append(sphere4);

		Model* sphere5 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere5->setLocation(-5,17, 2);
		sphere5->setForceColorOnly(true);
		sphere5->setModelColor(QColor(255,165,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere5->getCollider()));
		models.append(sphere5);

		Model* sphere6 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere6->setLocation(-7,17, 2);
		sphere6->setForceColorOnly(true);
		sphere6->setModelColor(QColor(255,165,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere6->getCollider()));
		models.append(sphere6);

		Model* sphere7 = new Model(spherePath.toStdString(), "Movable Obstacle", shader, &physicsSimulation, COLLISION_SPHERE);
		sphere7->setLocation(-6,20, 1);
		sphere7->setForceColorOnly(true);
		sphere7->setModelColor(QColor(255,255,0));
		physicsSimulation.registerPhysicsSphere(static_cast<PhysicsSphere*>(sphere7->getCollider()));
		models.append(sphere7);
	}

	emit updateModels();
}

//TODO: Not working!
void GLWidget::reinitializeScene()
{
	qDebug() << ">>>>>>>Reinitializing the Scene...<<<<<<<";
	physicsSimulation.quit();
	physicsSimulation.wait();
	qDeleteAll(models);
	models.clear();
	this->initializeScene();
}

void GLWidget::initializeGL(){
	initializeOpenGLFunctions();
	connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(teardownGL()), Qt::DirectConnection);
	connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));

	connect(windowUpdateTimer, SIGNAL(timeout()), this, SLOT(fireUpdateWindowTitle()));
	windowUpdateTimer->start(windowUpdateTime);
	printContextInformation();
	qDebug() << "ENGINE: Clock Precision is:" << LabEngine::HiResClock::period::den << "Ticks per Second." << "Clock is steady =" << LabEngine::HiResClock::is_steady;

	glEnable(GL_MULTISAMPLE); // Enable MSAA
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, renderType);
	glClearColor(0.0f,0.0f,0.0f,1.0f);


	// Populates the scene with Models
	initializeScene();

	//TODO: Write custom class that wraps around this with simple integers
	//TODO2: move to main again with thread synchronization and wait for completion of initializeGL
	auto version = context()->versionFunctions<QOpenGLFunctions_3_3_Core>();
	if(!version){
		qFatal(QString("FATAL ERROR: OPENGL VERSION INSUFFICIENT. REQUIRED: " + QString::number(format().version().first) + "." + QString::number(format().version().second)).toStdString().c_str());
		QCoreApplication::exit(-1);
	}

}

void GLWidget::resizeGL(int width, int height){
	projection.setToIdentity();
	projection.perspective(45.0f, float(width) / float(height), 0.01f, 1000.0f);
}

void GLWidget::paintGL(){

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
}

void GLWidget::fireUpdateWindowTitle()
{
	emit updateWindowTitle("Frame-Time: ");
	frameCount = 0;
}

void GLWidget::teardownGL(){
	qWarning() << "TEARING DOWN OPENGL";
}

void GLWidget::update(){
	++frameCount;
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
