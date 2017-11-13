#include "ShaderManager.h"
#include <QMultiMap>
#include <QMap>
#include "Shader.h"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	//TODO add delete arrays and pointers!
}

size_t ShaderManager::loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath){
	Shader* shader = new Shader();
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
		shaderList.push_back(shader);
	}
	return shaderList.size() - 1;
}

std::vector<Shader*> ShaderManager::getShaderList() const
{
	return shaderList;
}

Shader* ShaderManager::getShader(size_t id) const
{
	return shaderList[id];
}
