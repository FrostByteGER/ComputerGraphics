#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions>


class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT

	public:
		GLWindow();
		~GLWindow();
		void initializeGL();
		void resizeGL(int width, int height);
		void paintGL();
		void teardownGL();

	private:
		void printContextInformation();

		const QString vertexPath   = "Resources/Shaders/simple.vert";
		const QString fragmentPath = "Resources/Shaders/simple.frag";
		const QString cubePath     = "Resources/Models/cube.obj";
};

