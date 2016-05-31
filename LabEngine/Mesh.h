#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <QVector3D>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include "Shader.h"
#include "Transform3D.h"

class Model;
class Shader;

class Mesh
{
	public:
		Mesh(std::vector<QVector3D> vertices, std::vector<QVector3D> normals, std::vector<QVector2D> uvs, std::vector<GLuint> indices,
			 std::vector<QOpenGLTexture*> textures, Shader* shader, Model* parent);
		~Mesh();
		void DrawMesh(Shader* shader);
		static void generateSphere(std::vector<GLfloat>& outVertices, int size);

		std::vector<QVector3D> vertices;
		std::vector<QVector3D> normals;
		std::vector<QVector2D> uvs;
		std::vector<GLuint> indices;
		std::vector<QOpenGLTexture*> textures;

		size_t getShaderID() const;

		Transform3D getTransform() const;
		void setTransform(const Transform3D& value);

		Model* getParent() const;
		void setParent(Model* value);

		Shader* getShader() const;

	private:
		QString name;
		size_t shaderID;
		QOpenGLBuffer vertexBuffer;
		QOpenGLBuffer normalBuffer;
		QOpenGLBuffer uvBuffer;
		QOpenGLBuffer elementBuffer;
		QOpenGLVertexArrayObject vao;
		Shader* shader;
		int modelToWorld;
		Transform3D transform;
		Model* parent;

		void SetupMesh();
};

