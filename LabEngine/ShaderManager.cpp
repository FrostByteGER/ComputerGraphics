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

uint32_t ShaderManager::loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath){
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
	uint32_t id;
	if(result){

		id = LEUUID::generateUUID();
		shaderList.insert(id, shader);
	}
	return id;
}

QMap<uint32_t, QOpenGLShaderProgram*> ShaderManager::getShaderList() const
{
	return shaderList;
}

QOpenGLShaderProgram* ShaderManager::getShader(uint32_t id) const
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

QList<Mesh*> ShaderManager::getMeshes(uint32_t shaderID) const
{
	return modelList.values(shaderID);
}

QString ShaderManager::getShaderName() const
{
	//TODO add to QOpenGLShaderProgram
	return shaderName;
}

QMultiMap<uint32_t, Mesh*> ShaderManager::getModelList() const
{
	return modelList;
}

void ShaderManager::addMesh(uint32_t shaderID, Mesh* mesh)
{
	modelList.insert(shaderID, mesh);
}

void ShaderManager::removeMesh(const Mesh* mesh)
{
	modelList.remove(mesh->getShaderID());
}
