#include "Mesh.h"
#include <QDebug>
#include <memory>
#include "Model.h"

Mesh::Mesh(std::vector<QVector3D> vertices, std::vector<QVector3D> normals, std::vector<QVector2D> uvs, std::vector<GLuint> indices, std::vector<QOpenGLTexture*> textures, Shader* shader, Model* parent) :
	vertices(vertices), normals(normals), uvs(uvs), indices(indices), textures(textures),elementBuffer(QOpenGLBuffer::IndexBuffer), shader(shader), parent(parent)
{
	forceColorOnly = false;
	shader->addMesh(this);
	this->SetupMesh();
}

Mesh::~Mesh(){
	std::for_each(textures.begin(), textures.end(), std::default_delete<QOpenGLTexture>());
	shader->removeMesh(this);
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

	modelToWorld = shader->uniformLocation("modelToWorld");

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

	shader->setAttributeBuffer( "texCoords", GL_FLOAT, 0, 2 );
	shader->enableAttributeArray( "texCoords" );

	vao.release();
	elementBuffer.release();
	vertexBuffer.release();
	normalBuffer.release();
	uvBuffer.release();
}

void Mesh::DrawMesh(Shader* shader){
	vao.bind();
	{
		//qWarning() << "DRAWING MESH";
		{
			// Send the mesh transform to the vertex shader
			shader->setUniformValue(modelToWorld, parent->toMatrix());

			if(textures.size() == 0 || forceColorOnly){
				shader->setUniformValue("colorOnly", 1);
				shader->setUniformValue("fragColor", meshColor);
			}

			// Bind all textures
			uint32_t sizePerType = MAX_TEXTURE_SIZE / 4;
			for(GLuint i = 0; i < textures.size(); ++i){
				QOpenGLTexture* t = textures.at(i);
				if(!t){
					// Skip rest since its a nullptr.
					continue;
				}
				// Bind the texture
				t->bind(i);

				// Send the bound texture to the fragment shader
				if(i < sizePerType){ // Diffuse
					shader->setUniformValue("texture_diffuse" + i, i);
				}else if(i < sizePerType * 2){ // Specular
					shader->setUniformValue("texture_specular" + i - sizePerType, i);
				}else if(i < sizePerType * 3){ // Normal
					shader->setUniformValue("texture_normal" + i - sizePerType * 2, i);
				}else if(i < sizePerType * 4){ // Displacement
					shader->setUniformValue("texture_displacement" + i - sizePerType * 3, i);
				}
			}

			// Draw the mesh
			glDrawArrays(GL_TRIANGLES,0, vertices.size());

			// Release all textures
			for(QOpenGLTexture* t : textures){
				t->release();
			}
		}
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

size_t Mesh::getShaderID() const
{
	return shaderID;
}

Transform3D Mesh::getTransform() const
{
	return transform;
}

void Mesh::setTransform(const Transform3D& value)
{
	transform = value;
}

Model* Mesh::getParent() const
{
	return parent;
}

void Mesh::setParent(Model* value)
{
	parent = value;
}

Shader* Mesh::getShader() const
{
	return shader;
}

QColor Mesh::getMeshColor() const
{
	return meshColor;
}

void Mesh::setMeshColor(const QColor& value)
{
	meshColor = value;
}

bool Mesh::getForceColorOnly() const
{
	return forceColorOnly;
}

void Mesh::setForceColorOnly(const bool value)
{
	forceColorOnly = value;
}
