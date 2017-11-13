#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "Model.h"
#include "VTransform.h"
#include "Camera.h"
#include <chrono>
#include "Light.h"
#include <QVector>
#include "EngineClock.h"


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

	friend class MainWindow;

	public:
		GLWidget(QWidget* parent = nullptr);
		~GLWidget();
		void initializeGL();
		void resizeGL(int width, int height);
		void paintGL();

		void setWindowTitle(const QString& title);

	public slots:
		void updateWindowTitle();

	signals:
		void updateModels();

	protected:
		void keyPressEvent(QKeyEvent *event);
		void keyReleaseEvent(QKeyEvent *event);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);

	protected slots:
		void teardownGL();
		void update();

	private:
		EngineClock clock;
		void printContextInformation();
		Light directionalLight;
		QMatrix4x4 projection;
		int worldToCamera;
		int cameraToProjection;
		uint32_t windowUpdateTime;
		std::chrono::high_resolution_clock timer;
		QTimer* windowUpdateTimer;
		bool updateRenderType;
		GLint renderType;
		ShaderManager* shader;
		float derp;
		Camera camera;
		QVector<Model*> models;
		QString windowTitle;
		const QString vertexPath   = "Resources/Shaders/simple.vert";
		const QString fragmentPath = "Resources/Shaders/simple.frag";
		const QString cubePath     = "Resources/Models/crate/Crate.obj";
		const QString spherePath   = "Resources/Models/Sphere.obj";
		const QString customPath   = "Resources/Models/nanosuit/Nanosuit.obj";
		const QString floorPath    = "Resources/Models/Floor.obj";
};

