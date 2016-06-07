#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "Model.h"
#include "Transform3D.h"
#include "Camera.h"
#include <chrono>
#include "Scene.h"



class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT

	public:
		GLWindow();
		~GLWindow();
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

		QMatrix4x4 projection;
		int worldToView;
		int worldToCamera;
		int cameraToView;
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
		QString windowTitle;
		const QString vertexPath   = "Resources/Shaders/simple.vert";
		const QString fragmentPath = "Resources/Shaders/simple.frag";
		const QString cubePath     = "Resources/Models/crate/Crate.obj";
		const QString spherePath   = "Resources/Models/sphere.obj";
		const QString customPath   = "Resources/Models/nanosuit/nanosuit.obj";
};

