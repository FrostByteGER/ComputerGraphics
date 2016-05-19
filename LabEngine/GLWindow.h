#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "Model.h"
#include "Transform3D.h"
#include <QTime>


class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT

	public:
		GLWindow();
		~GLWindow();
		void initializeGL();
		void resizeGL(int width, int height);
		void paintGL();

	protected:
		virtual void keyPressEvent( QKeyEvent* e );

	protected slots:
		void teardownGL();
		void update();

	private:
		void printContextInformation();

		QMatrix4x4 projection;
		ShaderManager* shader;
		Model* model;
		Model* model2;
		QTime timer;
		const QString vertexPath   = "Resources/Shaders/simple.vert";
		const QString fragmentPath = "Resources/Shaders/simple.frag";
		const QString cubePath     = "Resources/Models/cube.obj";
		const QString spherePath   = "Resources/Models/sphere.obj";
};

