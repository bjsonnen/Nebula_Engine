#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include "GameObject.h"
#include "Camera.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "Skybox.h"
#include "Window.h"
#include "Shader.h"
#include "PointLight.h"

#include "Util.h"

#include <vector>

class RootManager
{
public:
	RootManager();

	// Camera, materials, lights, skybox creation; Shader compiling
	// Should be called after the window initialization and before the main loop
	void EngineInitialization(Window& window, Camera& cam, Material& mat1, Material& mat2, DirectionalLight& light,
		Skybox& skybox, std::vector<Shader>& shaderList);

	// Game rendering loop
	// Should be called once per frame
	void EngineUpdate(std::vector<GameObject*>* objectList, Camera& cam, PointLight* pointLights,
		SpotLight* spotLights, int pointCount, int spotCount, glm::mat4 projection,
		DirectionalLight* mainLight);

	// Load all objects
	// Should be called before the first frame. 
	void EngineLoading(std::vector<Texture*>* textureList, std::vector<GameObject*>* objectList, bool& loading);

	// Main game loop
	bool MainLoop(Window* window);

	// Compile user shader
	// Called only once at the initialization of the game engine
	void CompileCustomShaders(void* blubb);

	void GameStart();
	void GameUpdate();
	void GameLateUpdate();

	Window GetWindow() { return renderWindow; }
	Camera GetCamera() { return camera; }
	Shader GetDirectionalShadowShader() { return directionalShadowShader; }
	Shader GetOmniShadowShader() { return omniShadowShader; }

	std::vector<Shader>& GetShaderList() { return shaderList; }

	~RootManager();

private:
	void OmniShadowMapPass(PointLight* light);
	void DirectionalShadowMapPass(DirectionalLight* light);
	void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, PointLight* pointLights,
		SpotLight* spotLights, int pointlightCount, int spotlightCount);

	void CompileShaders();
	void RenderScene();

private:
	std::vector<Shader> shaderList;
	std::vector<GameObject*>* objectList;
	std::vector<Texture*> textureList;

	Shader directionalShadowShader;
	Shader omniShadowShader;

	Material defaultMaterial;

	DirectionalLight mainLight;

	Window renderWindow;
	Camera camera;
	Skybox skybox;

	unsigned int uniformModel;

	bool loading = true;
};

