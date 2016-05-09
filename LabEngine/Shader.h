#pragma once

#include <QOpenGLShaderProgram>



class Shader
{
	public:
		static QOpenGLShaderProgram* getInstance(){
			return &shader;
		}

		static bool loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath);

	private:
		static QOpenGLShaderProgram shader;
};

