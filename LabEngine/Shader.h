#pragma once
#include <QOpenGLShaderProgram>
#include "Mesh.h"

class Mesh;


class Shader : public QOpenGLShaderProgram
{
	public:
		Shader();
		~Shader();
		void addMesh(Mesh& m);
		void addMesh(Mesh* m);
		void removeMesh(const Mesh& m);
		void removeMesh(const Mesh* m);
		QString getShaderName() const;

		std::vector<Mesh*> getMeshes() const;
		void setMeshes(const std::vector<Mesh*>& value);

	private:
		std::vector<Mesh*> meshes;
		const QString shaderName;
};
