#pragma once

#include <vector>
#include "ShaderManager.h"
#include "Model.h"
#include "Player.h"
#include "Camera.h"

class GLWidget;

class Scene
{
	public:
		Scene();
		~Scene();

		void initScene();
		void renderScene();
		void updateScene();

	private:
		void teardownScene();

		GLWidget* parentContextContainer;
		std::vector<Player*> players;
		std::vector<Model*> models;
		ShaderManager* shaderManager;
};
