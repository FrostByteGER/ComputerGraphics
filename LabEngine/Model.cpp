#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.h"

Model::Model(const std::string& path)
{
	this->loadModel(path);
}

void Model::DrawModel(){
	for(Mesh& m : meshes){
		m.DrawMesh();
	}
}

void Model::loadModel(const std::string &path){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		qCritical() << "Assimp Error: " << importer.GetErrorString();
		return;
	}
	this->directory = path.substr(0,path.find_last_of('/'));
	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for(uint i = 0; i < node->mNumMeshes; ++i){
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene));
	}

	for(uint i = 0; i < node->mNumChildren; ++i){
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<QVector3D> vertices;
	std::vector<QVector3D> normals;
	std::vector<QVector2D> uvs;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

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

	for(uint i = 0; i < mesh->mNumFaces; ++i){
		aiFace face = mesh->mFaces[i];
		for(uint j = 0; j < face.mNumIndices; ++j){
			indices.push_back(face.mIndices[j]);
		}
	}

	if(mesh->mMaterialIndex >= 0){
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, normals, uvs, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for(uint i = 0; i < mat->GetTextureCount(type); ++i){
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		//texture.id = TextureFromFile(str.C_Str(), this->directory);
		texture.type = typeName;
		textures.push_back(texture);
	}
	return textures;
}
