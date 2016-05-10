#pragma once

#include <QOpenGLShaderProgram>



class Shader
{
	public:
		Shader();
		~Shader();
		bool loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath);
		QOpenGLShaderProgram* getShader() const;

	private:
		QOpenGLShaderProgram* shader;
};

