#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include "Model.h"


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

	private:
		void printContextInformation();

		Model* model;
		const QString vertexPath   = "Resources/Shaders/simple.vert";
		const QString fragmentPath = "Resources/Shaders/simple.frag";
		//TODO: Fix string path
		const QString cubePath     = "debug/Resources/Models/cube.obj";
};

