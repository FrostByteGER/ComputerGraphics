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

class Mesh
{
	public:
		Mesh(std::vector<QVector3D> vertices, std::vector<QVector3D> normals, std::vector<QVector2D> uvs, std::vector<GLuint> indices, std::vector<QOpenGLTexture*> textures, QOpenGLShaderProgram* shader);
		Mesh(Mesh& other);
		~Mesh();
		void DrawMesh(QOpenGLShaderProgram* shader);
		static void generateSphere(std::vector<GLfloat>& outVertices, int size);

		std::vector<QVector3D> vertices;
		std::vector<QVector3D> normals;
		std::vector<QVector2D> uvs;
		std::vector<GLuint> indices;
		std::vector<QOpenGLTexture*> textures;

		uint32_t getShaderID() const;

	private:
		QString name;
		uint32_t shaderID;
		QOpenGLBuffer vertexBuffer;
		QOpenGLBuffer normalBuffer;
		QOpenGLBuffer uvBuffer;
		QOpenGLBuffer elementBuffer;
		QOpenGLVertexArrayObject vao;
		QOpenGLShaderProgram* shader;
		QMatrix4x4 projection;
		Transform3D transform;

		void SetupMesh();
};

