#pragma once

#include <vector>
#include "Mesh.h"

class Model
{
	public:
		Model(const std::string& path);
		void DrawModel();

	private:
		std::vector<Mesh> meshes;
		std::string directory;
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

