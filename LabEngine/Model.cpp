#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QOpenGLTexture>
#include <memory>
#include "Model.h"

Model::Model(const std::string& path, ShaderManager* sm) : shaderManager(sm)
{
	this->name = QString::fromStdString(path.substr(path.find_last_of('/') + 1,std::string::npos));
	shaderID = shaderManager->loadShader("Resources/Shaders/simple.vert", "Resources/Shaders/simple.frag");
	qDebug() << "SHADERID: " <<shaderID;
	this->loadModel(path);

}

Model::~Model(){
	std::for_each(meshes.begin(), meshes.end(), std::default_delete<Mesh>());
}

void Model::DrawModel(){
	Shader* shader = shaderManager->getShader(shaderID);
	// If we don't have a shader, do NOT draw!
	if(!shader){
		return;
	}
	for(Mesh* m : meshes){
		m->DrawMesh(shader);
	}
}

void Model::loadModel(const std::string& path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		qCritical() << "Assimp Error: " << importer.GetErrorString();
		valid = false;
		return;
	}
	this->directory = path.substr(0,path.find_last_of('/'));
	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for(uint i = 0; i < node->mNumMeshes; ++i){
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		auto* processedMesh = this->processMesh(mesh, scene);
		this->meshes.push_back(processedMesh);
	}

	for(uint i = 0; i < node->mNumChildren; ++i){
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<QVector3D> vertices;
	std::vector<QVector3D> normals;
	std::vector<QVector2D> uvs;
	std::vector<GLuint> indices;
	std::vector<QOpenGLTexture*> textures;

	// Get Vertices, Normals and UVs
	for(uint i = 0; i < mesh->mNumVertices; ++i){
		QVector3D vertex(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertices.push_back(vertex);
		QVector3D normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		normals.push_back(normal);
		if(mesh->mTextureCoords[0]){
			QVector2D uv(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			uvs.push_back(uv);
		}else{
			uvs.push_back(QVector2D());
		}
	}

	// Get Indices
	for(uint i = 0; i < mesh->mNumFaces; ++i){
		aiFace face = mesh->mFaces[i];
		for(uint j = 0; j < face.mNumIndices; ++j){
			indices.push_back(face.mIndices[j]);
		}
	}

	// Get Materials
	if(mesh->mMaterialIndex >= 0){
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<QOpenGLTexture*> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<QOpenGLTexture*> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	// Return the constructed Mesh
	Shader* shader = shaderManager->getShader(shaderID);
	if(!shader){
		qWarning() << "SHADER NOT FOUND";
	}
	return new Mesh(vertices, normals, uvs, indices, textures, shader, this);
}

std::vector<QOpenGLTexture*> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	//TODO: Check if textures are already loaded! If so, don't reload the texture
	std::vector<QOpenGLTexture*> textures;
	for(uint i = 0; i < mat->GetTextureCount(type); ++i){
		aiString str;
		mat->GetTexture(type, i, &str);
		QOpenGLTexture* texture = loadTextureFromFile(std::string(str.C_Str()), this->directory);
		textures.push_back(texture);
	}
	return textures;
}

QOpenGLTexture* Model::loadTextureFromFile(const std::string& name, const std::string& directory){
	QOpenGLTexture* tex = new QOpenGLTexture(QImage(QString::fromStdString(directory + "/" + name)).mirrored());
	tex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	tex->setMagnificationFilter(QOpenGLTexture::Linear);
	return tex;
}

const VTransform& Model::getTransform() const
{
	return transform;
}

void Model::setTransform(const VTransform& value)
{
	transform = value;
}

const QVector3D& Model::getLocation() const
{
	return transform.translation();
}

void Model::setLocation(const QVector3D& location)
{
	transform.setTranslation(location);
}

void Model::setLocation(const float& x, const float& y, const float& z)
{
	transform.setTranslation(x, y, z);
}

const QVector3D& Model::getScale() const
{
	return transform.scale();
}

void Model::setScale(const QVector3D& scale)
{
	transform.setScale(scale);
}

void Model::setScale(const float& x, const float& y, const float& z)
{
	transform.setScale(x, y, z);
}

const QQuaternion& Model::getRotation() const
{
	return transform.rotation();
}

void Model::setRotation(const QQuaternion& rotation)
{
	transform.setRotation(rotation);
}

void Model::setRotation(const QVector3D& rotation)
{
	transform.setRotation(rotation);
}

void Model::setRotation(const float& x, const float& y, const float& z)
{
	transform.setRotation(x, y, z);
}

void Model::translate(const float& dx, const float& dy, const float& dz){
	transform.translate(dx, dy, dz);
}

void Model::translate(const QVector3D& translation){
	transform.translate(translation);
}

void Model::scale(const float& dx, const float& dy, const float& dz){
	transform.scale(dx, dy, dz);
}

void Model::scale(const float& uniformFactor){
	transform.scale(QVector3D(uniformFactor, uniformFactor, uniformFactor));
}

void Model::scale(const QVector3D& scale){
	transform.scale(scale);
}

void Model::rotate(const float& dyaw, const float& dpitch, const float& droll){
	transform.rotate(dyaw, dpitch, droll);
}

void Model::rotate(const float& angle, const QVector3D& axis){
	transform.rotate(angle, axis);
}

void Model::rotate(const float& angle, const float& dyaw, const float& dpitch, const float& droll){
	transform.rotate(angle, dyaw, dpitch, droll);
}

void Model::rotate(const QVector3D& drotation){
	transform.rotate(drotation);
}

void Model::rotate(const QQuaternion& drotation){
	transform.rotate(drotation);
}

QMatrix4x4 Model::toMatrix(){
	return transform.toMatrix();
}

QColor Model::getModelColor() const
{
	return modelColor;
}

void Model::setModelColor(const QColor& value)
{
	modelColor = value;
	for(Mesh* m : meshes){
		m->setMeshColor(value);
	}
}

void Model::setForceColorOnly(const bool& value)
{
	for(Mesh* m : meshes){
		m->setForceColorOnly(value);
	}
}

bool Model::isValid() const
{
	return valid;
}

QString Model::getName() const
{
	return name;
}
