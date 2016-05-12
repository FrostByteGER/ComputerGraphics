#pragma once

#include <QOpenGLShaderProgram>



class ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();
		QString loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath);
		std::map<QString, QOpenGLShaderProgram> getShaderList() const;
		QOpenGLShaderProgram* getShader(QString id) const;

	private:
		std::map<QString, QOpenGLShaderProgram*> shaderList;
};

