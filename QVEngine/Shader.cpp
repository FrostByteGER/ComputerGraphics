#include "Shader.h"
#include <vector>

Shader::Shader()
{

}

Shader::~Shader()
{

}

void Shader::addMesh(Mesh& m)
{
	meshes.push_back(&m);
}

void Shader::addMesh(Mesh* m)
{
	meshes.push_back(m);
}

void Shader::removeMesh(const Mesh& m)
{
	meshes.erase(std::remove(meshes.begin(), meshes.end(), &m), meshes.end());
}

void Shader::removeMesh(const Mesh* m)
{
	meshes.erase(std::remove(meshes.begin(), meshes.end(), m), meshes.end());
}

QString Shader::getShaderName() const
{
	return shaderName;
}

std::vector<Mesh*> Shader::getMeshes() const
{
	return meshes;
}

void Shader::setMeshes(const std::vector<Mesh*>& value)
{
	meshes = value;
}
