#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <QVector3D>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include "Shader.h"

class Mesh
{
	public:
		Mesh(std::vector<QVector3D> vertices, std::vector<QVector3D> normals, std::vector<QVector2D> uvs, std::vector<GLuint> indices, std::vector<QOpenGLTexture*> textures);
		Mesh(Mesh& other);
		~Mesh();
		void DrawMesh(Shader* shader);
		static void generateSphere(std::vector<GLfloat>& outVertices, int size);

		std::vector<QVector3D> vertices;
		std::vector<QVector3D> normals;
		std::vector<QVector2D> uvs;
		std::vector<GLuint> indices;
		std::vector<QOpenGLTexture*> textures;

	private:
		QOpenGLBuffer vertexBuffer;
		QOpenGLBuffer normalBuffer;
		QOpenGLBuffer uvBuffer;
		QOpenGLBuffer elementBuffer;
		QOpenGLVertexArrayObject vao;

		void SetupMesh();
};

