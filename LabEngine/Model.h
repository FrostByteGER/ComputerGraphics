#pragma once

#include <assimp/scene.h>
#include <vector>
#include "Mesh.h"
#include "ShaderManager.h"

class Model
{
	public:
		Model(const std::string& path, ShaderManager* sm);
		~Model();
		void DrawModel();

	private:
		QString name;
		uint32_t shaderID;
		ShaderManager* shaderManager;
		//TODO: Maybe change to smartpointer!
		std::vector<Mesh*> meshes;
		std::string directory;
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<QOpenGLTexture*> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		QOpenGLTexture* loadTextureFromFile(const std::string& name, const std::string& directory);
};

