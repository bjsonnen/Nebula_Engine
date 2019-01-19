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

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Ui.h"

#include <GLFW/glfw3.h>

class RootManager
{
public:
	RootManager() {}

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

	// Update all vector arrays with gameplay content
	void EngineVariablesUpdate(std::vector<Texture*>* textureList, std::vector<GameObject*>* objectList, 
		glm::mat4 projection);

	// Main game loop
	bool MainLoop(bool windowShouldClose, Window& window, void* Start, void* Update);

	// Compile user shader
	// Called only once at the initialization of the game engine
	void CompileCustomShaders(void* blubb);

	// Call this when the game has ended
	void ShutDown();

	// ----------------

	Window GetWindow() { return renderWindow; }
	Camera GetCamera() { return camera; }
	Shader GetDirectionalShadowShader() { return directionalShadowShader; }
	Shader GetOmniShadowShader() { return omniShadowShader; }

	// Returns a std::vector<Shader>& with all predefined shaders
	std::vector<Shader>& GetShaderList() { return shaderList; }

	~RootManager() {}

private:
	// Shadow calculation for point & spotlights
	void OmniShadowMapPass(PointLight* light);
	// Shadow calculation for normal directional lighting
	void DirectionalShadowMapPass(DirectionalLight* light);
	// Main render pass, uploads all variables/textures to the shader
	void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, PointLight* pointLights,
		SpotLight* spotLights, int pointlightCount, int spotlightCount);

	// Compile predefined shaders
	void CompileShaders();
	// Render all objects
	void RenderScene();

	// Creats the nebula logo used in the loading screen
	void CreateNebulaLogo();

private:
	std::vector<Shader> shaderList;
	std::vector<GameObject*>* objectList;
	std::vector<Texture*>* textureList;

	glm::mat4 projection;

	Shader directionalShadowShader;
	Shader omniShadowShader;
	Shader nebulaLogoShader;

	Material defaultMaterial;

	DirectionalLight mainLight;

	Window renderWindow;
	Camera camera;
	Skybox skybox;

	PointLight pointLights[MAX_POINT_LIGHTS];
	SpotLight spotLights[MAX_SPOT_LIGHTS];

	Ui debugWindow;

	Mesh nebulaEngineLogo;
	Texture nebulaLogo = Texture("Textures/dev.jpg");

	unsigned int uniformModel;

	bool loading = true;
	bool firstStart = true;
};

