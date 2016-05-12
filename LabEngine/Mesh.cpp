#include "Mesh.h"
#include <QDebug>
#include <memory>
#include <QOpenGLShaderProgram>

Mesh::Mesh(std::vector<QVector3D> vertices, std::vector<QVector3D> normals, std::vector<QVector2D> uvs, std::vector<GLuint> indices, std::vector<QOpenGLTexture*> textures, QOpenGLShaderProgram* shader) :
	vertices(vertices), normals(normals), uvs(uvs), indices(indices), textures(textures),elementBuffer(QOpenGLBuffer::IndexBuffer), shader(shader)
{
	this->SetupMesh();
}

Mesh::Mesh(Mesh& other) : vertices(other.vertices), normals(other.normals), uvs(other.uvs), indices(other.indices), textures(other.textures),elementBuffer(QOpenGLBuffer::IndexBuffer)
{
	//TODO verify working!
	//TODO delete?
}

Mesh::~Mesh(){
	std::for_each(textures.begin(), textures.end(), std::default_delete<QOpenGLTexture>());
}


void Mesh::SetupMesh(){
	vao.create();
	vao.bind();

	// Elementbuffer
	elementBuffer.create();
	elementBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	elementBuffer.bind();
	elementBuffer.allocate(&indices[0], indices.size() * sizeof(GLuint));

	// Vertexbuffer
	vertexBuffer.create();
	vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	vertexBuffer.bind();
	vertexBuffer.allocate(&vertices[0], vertices.size() * sizeof(QVector3D));

	shader->setAttributeBuffer( "vertexPosition_modelspace", GL_FLOAT, 0, 3 );
	shader->enableAttributeArray( "vertexPosition_modelspace" );

	// Normalbuffer
	normalBuffer.create();
	normalBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	normalBuffer.bind();
	normalBuffer.allocate(&normals[0], normals.size() * sizeof(QVector3D));

	// UVbuffer
	uvBuffer.create();
	uvBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	uvBuffer.bind();
	uvBuffer.allocate(&uvs[0], uvs.size() * sizeof(QVector2D));

	vao.release();
	elementBuffer.release();
	vertexBuffer.release();
	normalBuffer.release();
	uvBuffer.release();
}

void Mesh::DrawMesh(QOpenGLShaderProgram* shader){
	vao.bind();
	{
		qWarning() << "DRAWING MESH";
		shader->bind();
		{
			for(QOpenGLTexture* t : textures){
				t->bind();
			}
			glDrawArrays(GL_TRIANGLES,0,vertices.size());
			for(QOpenGLTexture* t : textures){
				t->release();
			}
		}
		shader->release();
	}
	vao.release();
}

void Mesh::generateSphere(std::vector<GLfloat>& outVertices ,int size)
{
	// Change to double parameter
	double pointAmount = static_cast<double>(size);
	double circle = M_PI*2.0;

	std::vector<GLfloat> circleXpoint = {};
	std::vector<GLfloat> circleYpoint = {};
	std::vector<GLfloat> circleZpoint = {};
	double circleAmount = circle/pointAmount;

	double circleRadius = 0.0;

	for (double z = 0.0; z < pointAmount+1; z++) {

		circleRadius = sin((circleAmount*z)/2.0);

		circleZpoint.push_back(cos((circleAmount*z)/2.0));

		for (double y = 0.0; y < size*circleAmount; y+=circleAmount) {

			circleXpoint.push_back(cos(y)*circleRadius);
			circleYpoint.push_back(sin(y)*circleRadius);
		}
	}

	int zint = 0;
	//TODO check if -1 is correct
	for(int i = 0 ; i < circleXpoint.size()-pointAmount-1 ; i++){

		if(i > 0 && (i%size) == 0){
			zint++;

		}
		if(i > 0 && (i%size) == size-1){

			outVertices.push_back(circleZpoint[zint]);
			outVertices.push_back(circleXpoint[i]);
			outVertices.push_back(circleYpoint[i]);

			outVertices.push_back(circleZpoint[zint+1]);
			outVertices.push_back(circleXpoint[i+size]);
			outVertices.push_back(circleYpoint[i+size]);

			outVertices.push_back(circleZpoint[zint+1]);
			outVertices.push_back(circleXpoint[i+1]);
			outVertices.push_back(circleYpoint[i+1]);

			outVertices.push_back(circleZpoint[zint+1]);
			outVertices.push_back(circleXpoint[i+1]);
			outVertices.push_back(circleYpoint[i+1]);

			outVertices.push_back(circleZpoint[zint+1]);
			outVertices.push_back(circleXpoint[i+size]);
			outVertices.push_back(circleYpoint[i+size]);

			outVertices.push_back(circleZpoint[zint+2]);
			outVertices.push_back(circleXpoint[i+size+1]);
			outVertices.push_back(circleYpoint[i+size+1]);
		}else{
			outVertices.push_back(circleZpoint[zint]);
			outVertices.push_back(circleXpoint[i]);
			outVertices.push_back(circleYpoint[i]);

			outVertices.push_back(circleZpoint[zint+1]);
			outVertices.push_back(circleXpoint[i+size]);
			outVertices.push_back(circleYpoint[i+size]);

			outVertices.push_back(circleZpoint[zint]);
			outVertices.push_back(circleXpoint[i+1]);
			outVertices.push_back(circleYpoint[i+1]);

			outVertices.push_back(circleZpoint[zint]);
			outVertices.push_back(circleXpoint[i+1]);
			outVertices.push_back(circleYpoint[i+1]);

			outVertices.push_back(circleZpoint[zint+1]);
			outVertices.push_back(circleXpoint[i+size]);
			outVertices.push_back(circleYpoint[i+size]);

			outVertices.push_back(circleZpoint[zint+1]);
			outVertices.push_back(circleXpoint[i+size+1]);
			outVertices.push_back(circleYpoint[i+size+1]);
		}
	}
}
