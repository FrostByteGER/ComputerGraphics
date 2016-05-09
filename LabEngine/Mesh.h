#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <QVector3D>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "Shader.h"

struct Texture{
		GLuint id;
		std::string type;
};


class Mesh
{
	public:
		Mesh(std::vector<QVector3D> vertices,std::vector<QVector3D> normals, std::vector<QVector2D> uvs, std::vector<GLuint> indices, std::vector<Texture> textures);
		Mesh(Mesh& other);
		void DrawMesh();
		static void Mesh::generateSphere(std::vector<GLfloat>& outVertices, int size);

		std::vector<QVector3D> vertices;
		std::vector<QVector3D> normals;
		std::vector<QVector2D> uvs;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

	private:
		QOpenGLBuffer vertexBuffer;
		QOpenGLBuffer normalBuffer;
		QOpenGLBuffer uvBuffer;
		QOpenGLBuffer elementBuffer;
		QOpenGLVertexArrayObject vao;

		void SetupMesh();
};

