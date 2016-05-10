#include "Shader.h"

Shader::Shader()
{
	shader = new QOpenGLShaderProgram();
}

Shader::~Shader()
{
	delete shader;
}

bool Shader::loadShader(const QString& vertexShaderPath, const QString& fragmentShaderPath){
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
	return result;
}

QOpenGLShaderProgram* Shader::getShader() const
{
	return shader;
}
