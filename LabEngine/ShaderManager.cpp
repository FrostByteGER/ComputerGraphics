#include "ShaderManager.h"
#include "UUID.h"
#include <QMultiMap>
#include <QMap>

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	//TODO add delete arrays and pointers!
}

GLuint ShaderManager::loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath){
	QOpenGLShaderProgram* shader = new QOpenGLShaderProgram();
	// Load Vertex Shader
	bool result = shader->addShaderFromSourceFile( QOpenGLShader::Vertex, vertexShaderPath );
	if ( !result ){
		qWarning() << shader->log();
	}
	// Load Fragment Shader
	result = shader->addShaderFromSourceFile( QOpenGLShader::Fragment, fragmentShaderPath );
	if ( !result ){
		qWarning() << shader->log();
	}

	// Link the Shader
	result = shader->link();
	if ( !result ){
		qWarning() << "Could not link shader program:" << shader->log();
	}
	if(result){
		//TODO Change ID to QOpenGLShaderProgram::programId()
		shaderList.insert(shader->programId(), shader);
	}
	return shader->programId();
}

QMap<GLuint, QOpenGLShaderProgram*> ShaderManager::getShaderList() const
{
	return shaderList;
}

QOpenGLShaderProgram* ShaderManager::getShader(GLuint id) const
{
	QOpenGLShaderProgram* value = nullptr;
	for(auto i = shaderList.find(id); i != shaderList.end() ; ++i){
		value = i.value();
	}
	return value;
}

std::vector<Mesh*> ShaderManager::getMeshes() const
{
	return modelList.values().toVector().toStdVector();
}

QList<Mesh*> ShaderManager::getMeshes(GLuint shaderID) const
{
	return modelList.values(shaderID);
}

QString ShaderManager::getShaderName() const
{
	//TODO add to QOpenGLShaderProgram
	return shaderName;
}

QMultiMap<GLuint, Mesh*> ShaderManager::getModelList() const
{
	return modelList;
}

void ShaderManager::addMesh(GLuint shaderID, Mesh* mesh)
{
	modelList.insert(shaderID, mesh);
}

void ShaderManager::removeMesh(const Mesh* mesh)
{
	modelList.remove(mesh->getShaderID());
}
