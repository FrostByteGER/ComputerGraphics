#pragma once

#include <vector>
#include "ShaderManager.h"
#include "Model.h"
#include "Player.h"
#include "Camera.h"

class GLWindow;

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

		GLWindow* parentContextContainer;
		std::vector<Player*> players;
		std::vector<Model*> models;
		ShaderManager* shaderManager;
};
