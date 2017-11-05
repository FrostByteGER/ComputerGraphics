#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "Model.h"
#include "VTransform.h"
#include "Camera.h"
#include <chrono>
#include "Scene.h"
#include "Light.h"
#include "PhysicsThread.h"



class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

	public:
		GLWidget(QWidget* parent = nullptr);
		~GLWidget();
		void initializeGL();
		void resizeGL(int width, int height);
		void paintGL();

		void setWindowTitle(const QString& title);

	public slots:
		void updateWindowTitle();

	protected:
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

	protected slots:
		void teardownGL();
		void update();

	private:
		void printContextInformation();
		Scene* scene;
		PhysicsThread physicsSimulation;
		Light directionalLight;
		QMatrix4x4 projection;
		int worldToCamera;
		int cameraToProjection;
		double deltaTimeNS;
		double deltaTimeMS;
		uint32_t windowUpdateTime;
		std::chrono::high_resolution_clock timer;
		QTimer* windowUpdateTimer;
		bool updateRenderType;
		GLint renderType;
		ShaderManager* shader;
		Camera camera;
		Model* model;
		Model* model2;
		Model* model3;
		Model* model4;
		QString windowTitle;
		const QString vertexPath   = "Resources/Shaders/simple.vert";
		const QString fragmentPath = "Resources/Shaders/simple.frag";
		const QString cubePath     = "Resources/Models/crate/Crate.obj";
		const QString spherePath   = "Resources/Models/Sphere.obj";
		const QString customPath   = "Resources/Models/nanosuit/Nanosuit.obj";
};

