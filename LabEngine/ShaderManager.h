#pragma once

#include <QOpenGLShaderProgram>
#include <QMultiMap>
#include <QMap>
#include "Mesh.h"
#include "Shader.h"



class ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();
		size_t loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath);
		size_t loadShader();
		std::vector<Shader*> getShaderList() const;
		Shader* getShader(size_t id) const;

	private:
		std::vector<Shader*> shaderList;
		const QString vertexPath   = ":/Resources/Shaders/simple.vert";
		const QString fragmentPath = ":/Resources/Shaders/simple.frag";
};

