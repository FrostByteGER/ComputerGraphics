#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <QVector3D>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include "Transform3D.h"

class Model;

class Mesh
{
	public:
		Mesh(std::vector<QVector3D> vertices, std::vector<QVector3D> normals, std::vector<QVector2D> uvs, std::vector<GLuint> indices,
			 std::vector<QOpenGLTexture*> textures, QOpenGLShaderProgram* shader, Model* parent);
		Mesh(Mesh& other);
		~Mesh();
		void DrawMesh(QOpenGLShaderProgram* shader);
		static void generateSphere(std::vector<GLfloat>& outVertices, int size);

		std::vector<QVector3D> vertices;
		std::vector<QVector3D> normals;
		std::vector<QVector2D> uvs;
		std::vector<GLuint> indices;
		std::vector<QOpenGLTexture*> textures;

		GLuint getShaderID() const;

		Transform3D getTransform() const;
		void setTransform(const Transform3D& value);

		Model* getParent() const;
		void setParent(Model* value);

	private:
		QString name;
		GLuint shaderID;
		QOpenGLBuffer vertexBuffer;
		QOpenGLBuffer normalBuffer;
		QOpenGLBuffer uvBuffer;
		QOpenGLBuffer elementBuffer;
		QOpenGLVertexArrayObject vao;
		QOpenGLShaderProgram* shader;
		int modelToWorld;
		Transform3D transform;
		Model* parent;

		void SetupMesh();
};

