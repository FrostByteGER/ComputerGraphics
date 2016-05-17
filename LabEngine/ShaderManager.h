#pragma once

#include <QOpenGLShaderProgram>
#include <QMultiMap>
#include <QMap>
#include "Mesh.h"



class ShaderManager
{
	public:
		ShaderManager();
		~ShaderManager();
		uint32_t loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath);
		QMap<uint32_t, QOpenGLShaderProgram*> getShaderList() const;
		QOpenGLShaderProgram* getShader(uint32_t id) const;
		std::vector<Mesh*> getMeshes() const;
		QList<Mesh*> getMeshes(uint32_t shaderID) const;
		QString getShaderName() const;
		QMultiMap<uint32_t, Mesh*> getModelList() const;
		void addMesh(uint32_t shaderID, Mesh* mesh);
		void ShaderManager::removeMesh(const Mesh* mesh);

	private:
		QString shaderName;
		QMap<uint32_t, QOpenGLShaderProgram*> shaderList;
		QMultiMap<uint32_t, Mesh*> modelList;
};

