#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <stdlib.h>
#include <thread>

#include "CommonValues.h"

#include "Window.h"
#include "Util.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "Audio.h"
#include "Math.h"

#include "Hdr.h"

#include "Model.h"

#include "Skybox.h"
#include "main.h"
#include "Highlights.h"

// math
const float toRadians = 3.14159265f / 180.0f;

// settings
bool loading = true;
float tmp = 0.0f;
bool hdr = true;
bool hdrKeyPressed = false;
float exposure = 1.0f;

// uniform variables
unsigned int uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0,
uniformDirectionalLightTransform = 0, uniformOmniLightPos = 0, uniformFarPlane = 0;

// lists
std::vector<Mesh*> meshList;
std::vector<Model*> modelList;
std::vector<Texture*> textureList;
std::vector<Shader> shaderList;

// objects
Window renderWindow;

Shader directionalShadowShader;
Shader omniShadowShader;

Camera camera;

Shader* shader2;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture devTexture;
Texture nebulaLogo;

Material shinyMaterial;
Material dullMaterial;

Model spider;
Model model;
Model blackhawk;
Model house;
Model barrel;

Mesh NebulaEngineLogo;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Skybox skybox;

Audio secondAudio = Audio("trump.mp3");

Util util;

// variables
unsigned int pointLightCount = 0;
unsigned int spotLightCount = 0;

glm::mat4 projection;

float deltaTime = 0.0f;
float lastTime = 0.0f;

float blackhawkAngle = 0.0f;

// Compile all shaders & add to list
void CompileShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");
	shaderList.push_back(*shader1);

	shader2 = new Shader();
	shader2->CreateFromFiles("Shaders/logo.vert", "Shaders/logo.frag");

	directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");
	omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag");
}

// Render all objects
void RenderScene()
{
	glm::mat4 model;

	for (int i = 0; i < modelList.size(); i++)
	{
		model = glm::mat4();
		model = glm::translate(model, modelList[i]->GetPosition() *= -1);
		model = glm::rotate(model, 90.0f * toRadians, modelList[i]->GetRotation());
		model = glm::scale(model, modelList[i]->GetScale());
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		modelList[i]->RenderModel();
	}

}

void DirectionalShadowMapPass(DirectionalLight* light)
{
	directionalShadowShader.UseShader();

	glViewport(0, 0, light->getShadowMap()->GetShadowWidth(), light->getShadowMap()->GetShadowHeight());

	light->getShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = directionalShadowShader.GetModelLocation();
	directionalShadowShader.SetDirectionalLightTransform(&light->CalculateLightTransform());

	directionalShadowShader.Validate();

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OmniShadowMapPass(PointLight* light)
{
	omniShadowShader.UseShader();

	glViewport(0, 0, light->getShadowMap()->GetShadowWidth(), light->getShadowMap()->GetShadowHeight());

	light->getShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = omniShadowShader.GetModelLocation();
	uniformOmniLightPos = omniShadowShader.GetOmniLightPosLocation();
	uniformFarPlane = omniShadowShader.GetFarPlaneLocation();

	glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
	glUniform1f(uniformFarPlane, light->GetFarPlane());
	omniShadowShader.SetLightMatrices(light->CalculateLightTransform());

	omniShadowShader.Validate();

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Upload uniform variables
void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	glViewport(0, 0, renderWindow.GetWindowWidth(), renderWindow.GetWindowHeight());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkybox(viewMatrix, projectionMatrix);

	shaderList[0].UseShader();

	// Get shader position
	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformModel = shaderList[0].GetModelLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();

	// Upload matrices
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePosition, camera.GetCameraPosition().x, camera.GetCameraPosition().y, camera.GetCameraPosition().z);

	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointLightCount, 3, 0);
	shaderList[0].SetSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
	shaderList[0].SetDirectionalLightTransform(&mainLight.CalculateLightTransform());

	mainLight.getShadowMap()->Read(GL_TEXTURE2);
	shaderList[0].SetTexture(1);
	shaderList[0].SetDirectionalShadowMap(2);

	glm::vec3 lowerLight = camera.GetCameraPosition();
	lowerLight.y -= 0.3f;
	spotLights[0].SetFlash(lowerLight, camera.GetCameraDirection());

	shaderList[0].Validate();

	RenderScene();
}

// Used to create the logo for the loading screen
void CreateLogo()
{
	float vertices[] =
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	util.CalculateNormals(indices, 6, vertices, 32, 8, 5);

	NebulaEngineLogo.CreateMesh(vertices, indices, 32, 6);
}

void LoadData()
{
	// Load textures into ram
	for (int i = 0; i < textureList.size(); i++)
	{
		textureList[i]->LoadTexture();
	}

	// Load mesh data & textures into ram
	for (int i = 0; i < modelList.size(); i++)
	{
		modelList[i]->LoadModel();
	}

	// Loading screen finished
	loading = false;
}

int main() 
{
	renderWindow = Window(1280, 720);
	renderWindow.Initialise();
	//renderWindow.SetIcon("C:/Users/Björn Sonnen/Desktop/icon.png");

	EngineInitialization();

	float cooldown = 0.0f;

	// Define Textures
	// => Model load all Textures automaticly
	brickTexture = Texture("Textures/brick.png");
	textureList.push_back(&brickTexture);
	dirtTexture = Texture("Textures/dirt.png");
	textureList.push_back(&dirtTexture);
	plainTexture = Texture("Textures/plain.png");
	textureList.push_back(&plainTexture);
	devTexture = Texture("Textures/dev.jpg");
	textureList.push_back(&devTexture);
	nebulaLogo = Texture("Textures/sara.jpg");
	textureList.push_back(&nebulaLogo);

	// Define Models
	CreateLogo();
	
	spider = Model("Models/spider.obj");
	spider.SetPosition(glm::vec3(10.0f, 20.0f, 10.0f));
	spider.SetScale(glm::vec3(0.006f, 0.006f, 0.006f));
	modelList.push_back(&spider);

	blackhawk = Model("Models/uh60.obj");
	blackhawk.SetPosition(glm::vec3(1.0f, 2.0f, -10.0f));
	blackhawk.SetScale(glm::vec3(0.4f, 0.4f, 0.4f));
	modelList.push_back(&blackhawk);

	Model meshtest = Model("Models/spider.obj");
	meshtest.SetPosition(glm::vec3(-10.0f, -10.0f, -10.0f));
	modelList.push_back(&meshtest);

	float tmp = 0.0f;

	while (!renderWindow.GetShouldClose())
	{
		// => Loading Screen Image
		if (loading)
		{

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//shader2->UseShader();

			//uniformProjection = shader2->GetProjectionLocation();
			//uniformView = shader2->GetViewLocation();
			//uniformModel = shader2->GetModelLocation();

			//tmp += renderWindow.GetDeltaTime();

			//glm::mat4 model;
			//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
			//model = glm::rotate(model, 90 * toRadians, glm::vec3(tmp, tmp, tmp));
			//model = glm::translate(model, glm::vec3(tmp, tmp, tmp));

			//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
			//glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
			//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

			//nebulaLogo.UseTexture();
			//NebulaEngineLogo.RenderMesh();

			renderWindow.SwapBuffers();
		}

		float now = glfwGetTime(); 
		deltaTime = now - lastTime;
		lastTime = now;
		
		renderWindow.WindowUpdate();
		
		Hdr hdr;

		// => Load Data
		if (!loading)
		{
			Update(projection);
		}
		else
			LoadData();

		renderWindow.SwapBuffers();
	}

	return 0;
}

void EngineInitialization()
{
	CompileShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	Highlights hl;
	//hl.GameStart();

	shinyMaterial = Material(1.0f, 4);
	dullMaterial = Material(0.3f, 4);

	mainLight = DirectionalLight(2048, 2048,
		1.0f, 0.9568627f, 0.8392157f,
		0.026f, 0.9f,
		-10.0f, -12.0f, 18.5f);

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/lagoon_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_up.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_ft.tga");

	skybox = Skybox(skyboxFaces);

	unsigned int uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;

	projection = glm::perspective(glm::radians(60.0f), (float)renderWindow.GetBufferWidth() / renderWindow.GetBufferHeight(), camera.GetNear(), camera.GetFar());
}

void Update(const glm::mat4 &projection)
{
	// Camera update
	camera.KeyControl(renderWindow.GetWindow(), deltaTime);
	camera.MouseControl(renderWindow.getXChange(), renderWindow.getYChange());

	if(renderWindow.Key(Window::KeyCode::Q))
		camera.SetTarget(blackhawk.GetPosition());

	if (renderWindow.Key(Window::KeyCode::B, Window::KeyAction::KeyDown))
	{
		secondAudio.Play();
	}

	if (renderWindow.Key(Window::KeyCode::L))
	{
		spotLights[0].Toggle();
	}

	if (renderWindow.Key(Window::KeyCode::R))
	{
		renderWindow.ShowMouse(false);
	}

	secondAudio.Update();
	
	glm::vec3 pos = modelList[1]->GetPosition();

	renderWindow.SetTitle("Nebula Engine // FPS: " + std::to_string(renderWindow.GetFPS()));

	// => Update a position every frame
	Math math;
	//modelList[1]->SetPosition(glm::vec3(pos.x - deltaTime, pos.y + deltaTime, pos.z - deltaTime));
	//modelList[0]->SetPosition(math.Lerp(modelList[0]->GetPosition(), modelList[1]->GetPosition(), deltaTime));
	
	DirectionalShadowMapPass(&mainLight);

	RenderPass(camera.CalculateViewMatrix(), projection);
}
