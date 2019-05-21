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
//#include "CommonValues.h"

#include "Util.h"

#include <vector>
#include <map>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Ui.h"

#include "ECManager.h"

#include <GLFW/glfw3.h>

//! Main class for all automatic processes. 
class RootManager
{
public:
	//! Create rootmanager object with standard parameters
	RootManager() {};

	//! Camera, materials, lights, skybox creation; Shader compiling
	//! Should be called after the window initialization and before the main loop
	//! @param window Insert main Window as Window&
	//! @param mat1 Insert first main Material as Material&
	//! @param mat2 Insert second main Material as Material&
	//! @param light Insert main Directional light as DirectionalLight&
	//! &param skybox Insert skybox as Skybox&
	//! &param shaderList Insert shaderList as std::vector<Shader>&
	void EngineInitialization(Window& window, Camera& cam, Material& mat1, Material& mat2, DirectionalLight& light,
		Skybox& skybox, std::vector<Shader>& shaderList);

	//! Game rendering loop
	//! Should be called once per frame
	//! @param cam Insert main Camera object as Camera&
	//! @param mainLight Insert directional Light as DirectionalLight*
	void EngineUpdate(Camera& cam, DirectionalLight* mainLight);

	//! Load all objects
	//! Should be called before the first frame
	void EngineLoading();

	//! Update all vector arrays with gameplay content
	//! @param textureList Insert main texturelist as std::vector<Texture*>* 
	//! @param objectList Insert main objectList as std::vector<GameObject*>*
	//! @param projection Insert projection as 4x4 matrix (glm::mat4)
	//! @param points Insert array pointer to you pointlight array
	//! @param spots Insert array pointer to you spotlight array
	//! @param pointsCount Insert array size of pointlight array
	//! @param spotsCount Insert array size of spotLights array
	void EngineVariablesUpdate(std::vector<Texture*>* textureList, std::vector<GameObject*>* objectList, 
		glm::mat4 projection, PointLight* points, SpotLight* spots, unsigned int pointsCount, 
		unsigned int spotsCount);

	//! Main game loop
	//! @param windowShouldClose Insert if the window should close as bool
	//! @param window Insert window as Window&
	//! @param Start Insert a void pointer to your start function
	//! @param Update Insert a void pointer to your update function
	//! @return Returns false if the loop has finished (bool)
	bool MainLoop(bool windowShouldClose, Window& window, void* Start, void* Update);

	//! Compile user shader
	//! Called only once at the initialization of the game engine
	//! @param blubb Pointer to the methode where to create the shaders
	void CompileCustomShaders(void* blubb);

	//! Call this when the game has ended
	void ShutDown();

	// ----------------

	//! Returns the current window
	//! @return Returns the window as object
	Window GetWindow() { return *renderWindow; }
	bool GetWindowActive() { return glfwWindowShouldClose(renderWindow->GetWindow()); }
	//! Returns the current camera
	//! @return Returns the camera object
	Camera GetCamera() { return camera; }
	//! Returns the shader for directional shadow
	//! @return Returns a shader object
	Shader GetDirectionalShadowShader() { return directionalShadowShader; }
	//! Returns the shader for omnishadow 
	//! @return Returns a shader object
	Shader GetOmniShadowShader() { return omniShadowShader; }

	//! Returns the main manager for entity-compoent-system
	//! Entity-component-system is not the same as RootManager
	//! @return Returns a manager as Manager
	//! @see Manager
	Manager* GetECSManager() { return manager; }

	//! Returns a std::vector<Shader>& with all predefined shaders
	//! @return Returns a std::vector<Shader>&
	std::vector<Shader>& GetShaderList() { return shaderList; }

	~RootManager() {}

private:
	//! Shadow calculation for point & spotlights
	void OmniShadowMapPass(PointLight* light);
	//! Shadow calculation for normal directional lighting
	void DirectionalShadowMapPass(DirectionalLight* light);
	//! Main render pass, uploads all variables/textures to the shader
	void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, PointLight* pointLights,
		SpotLight* spotLights, int pointlightCount, int spotlightCount);

	//! Search for blending objects in main object list
	void CheckForBlendedObjects();

	//! Compile predefined shaders
	void CompileShaders();
	//! Render all objects
	void RenderScene();

	//! Render a quad, used for HDR
	void RenderQuad();

private:
	std::vector<Shader> shaderList;
	std::vector<GameObject*>* objectList;
	std::vector<GameObject> transparentObjectList;
	std::vector<Texture*>* textureList;
	std::map<float, GameObject*> test;

	Texture texTest;

	glm::mat4 projection;

	Shader directionalShadowShader;
	Shader omniShadowShader;
	Shader hdrRendering;

	Material defaultMaterial;

	DirectionalLight mainLight;

	Window *renderWindow;
	Camera camera;
	Skybox skybox;

	PointLight pointLights[MAX_POINT_LIGHTS];
	SpotLight spotLights[MAX_SPOT_LIGHTS];

	PointLight* points;
	SpotLight* spots;

	unsigned int pointCount;
	unsigned int spotsCount;

	unsigned int quadVAO = 0;
	unsigned int quadVBO = 0;

	unsigned int hdrFBO = 0;
	unsigned int colorBuffer = 0;
	unsigned int rboDepth = 0;

	// Entity-Component-System Manager
	Manager* manager;

	Ui debugWindow;

	Mesh nebulaEngineLogo;
	Texture nebulaLogo = Texture("Textures/dev.jpg");

	unsigned int uniformModel;

	bool loading = true;
	bool firstStart = true;
};

