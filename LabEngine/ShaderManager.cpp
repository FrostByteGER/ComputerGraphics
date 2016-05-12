#include "ShaderManager.h"
#include <map>

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

QString ShaderManager::loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath){
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
	QString id;
	if(result){

		id = QString("TESTSHADER");
		shaderList.insert(std::make_pair(id, shader));
	}
	return id;
}

QOpenGLShaderProgram* ShaderManager::getShader(QString id) const
{
	auto position = shaderList.find(id);
	if(position == shaderList.end()){
		return nullptr;
	}else{
		return position->second;
	}
}
