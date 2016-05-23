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
		GLuint loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath);
		QMap<GLuint, QOpenGLShaderProgram*> getShaderList() const;
		QOpenGLShaderProgram* getShader(GLuint id) const;
		std::vector<Mesh*> getMeshes() const;
		QList<Mesh*> getMeshes(GLuint shaderID) const;
		QString getShaderName() const;
		QMultiMap<GLuint, Mesh*> getModelList() const;
		void addMesh(GLuint shaderID, Mesh* mesh);
		void removeMesh(const Mesh* mesh);

	private:
		QString shaderName;
		QMap<GLuint, QOpenGLShaderProgram*> shaderList;
		QMultiMap<GLuint, Mesh*> modelList;
};

