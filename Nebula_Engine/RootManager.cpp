#include "RootManager.h"

RootManager::RootManager()
{
}

void RootManager::EngineInitialization(Window& window, Camera& cam, Material& mat1, Material& mat2, DirectionalLight& light,
	Skybox& skybox, std::vector<Shader>& shaderList)
{
	CompileShaders();

	renderWindow = window;

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	mat1 = Material(1.0f, 4);
	defaultMaterial = mat1;
	mat2 = Material(0.3f, 4);

	light = DirectionalLight(2048, 2048,
		1.0f, 0.9568627f, 0.8392157f,
		0.026f, 0.9f,
		-10.0f, -12.0f, 18.5f);

	mainLight = light;

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/lagoon_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_up.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/lagoon_ft.tga");
	skybox = Skybox(skyboxFaces);
	this->skybox = skybox;
}

void RootManager::EngineUpdate(std::vector<GameObject*>* objectList, Camera& cam, PointLight* pointLights, 
	SpotLight* spotLights, int pointCount, int spotCount, glm::mat4 projection, 
	DirectionalLight* mainLight)
{
	// Performance issue: Dont store objectList in this->objectList
	this->objectList = objectList;

	DirectionalShadowMapPass(mainLight);

	for (int i = 0; i < pointCount; i++)
	{
		OmniShadowMapPass(&pointLights[i]);
	}

	for (int i = 0; i < spotCount; i++)
	{
		OmniShadowMapPass(&spotLights[i]);
	}

	RenderPass(cam.CalculateViewMatrix(), projection, pointLights, spotLights, pointCount, spotCount);
	RenderScene();
}

void RootManager::EngineLoading(std::vector<Texture*>* textureList, std::vector<GameObject*>* objectList, 
	bool& loading)
{
	for (int i = 0; i < textureList->size(); i++)
	{
		NE_ERROR_CHECK(textureList->at(i)->LoadTexture());
	}

	for (int i = 0; i < objectList->size(); i++)
	{
		NE_ERROR_CHECK(objectList->at(i)->LoadModel());
	}

	loading = false;
}

bool RootManager::MainLoop(Window * window)
{
	while (!window->GetShouldClose())
	{
		// Loading
		if (loading)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// ToDo
			//shader2->UseShader();

			//tmp += renderWindow.GetDeltaTime();

			//glm::mat4 model = glm::mat4();

			//model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -2.0f));

			//shader2->SetMatrix("projection", projection);
			//shader2->SetMatrix("view", camera.CalculateViewMatrix());
			//shader2->SetMatrix("model", model);

			//shader2->SetTexture("sTexture", 0);

			//nebulaLogo.UseTexture(GL_TEXTURE0);
			//NebulaEngineLogo.RenderMesh();

			renderWindow.SwapBuffers();
		}

		renderWindow.WindowUpdate();
		renderWindow.SetVSync(false);

		if (!loading)
		{
			camera.KeyControl(renderWindow.GetWindow(), renderWindow.GetDeltaTime());
			camera.MouseControl(renderWindow.GetXChange(), renderWindow.GetYChange());

			/*manager.Update();
			Update();*/
		}
		else
		{
			// ToDo
			EngineLoading(&textureList, objectList, loading);
		}

		EngineUpdate(objectList, camera, new PointLight(), new SpotLight(), 0, 0, glm::mat4(), &mainLight);

		renderWindow.SwapBuffers();
	}
	return false;
}

void RootManager::CompileCustomShaders(void * blubb)
{
	((void(*)(void))blubb)();
}

void RootManager::RenderScene()
{
	glm::mat4 model;

	//for (int i = 0; i < objectList.size(); i++)
	//{
	//	model = glm::mat4();
	//	model = glm::translate(model, objectList[i]->GetPosition());
	//	model = glm::rotate(model, Math::ToRadians(objectList[i]->GetDegrees()), objectList[i]->GetRotation());
	//	model = glm::scale(model, objectList[i]->GetScale());
	//	shaderList[0].SetBool("renderNormalMaps", objectList[i]->GetRenderNormalMaps());
	//	shaderList[0].SetMatrix("model", model);
	//	shaderList[0].SetVector3("primaryColor", objectList[i]->GetMainColor());
	//	if(uniformModel != 0)
	//		glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(model));
	//	defaultMaterial.UseMaterial(&shaderList[0]);
	//	objectList[i]->RenderModel();
	//}

	for (int i = 0; i < objectList->size(); i++)
	{
		model = glm::mat4();
		model = glm::translate(model, objectList->at(i)->GetPosition());
		model = glm::rotate(model, Math::ToRadians(objectList->at(i)->GetDegrees()), objectList->at(i)->GetRotation());
		model = glm::scale(model, objectList->at(i)->GetScale());
		shaderList[0].SetBool("renderNormalMaps", objectList->at(i)->GetRenderNormalMaps());
		shaderList[0].SetMatrix("model", model);
		shaderList[0].SetVector3("primaryColor", objectList->at(i)->GetMainColor());
		if (uniformModel != 0)
			glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(model));
		defaultMaterial.UseMaterial(&shaderList[0]);
		objectList->at(i)->RenderModel();
	}

	uniformModel = 0;
}

void RootManager::CompileShaders()
{
	Shader* shader1 = new Shader();
	NE_ERROR_CHECK(shader1->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag"));
	shaderList.push_back(*shader1);
	
	NE_ERROR_CHECK(directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag"));

	NE_ERROR_CHECK(omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag"));
}

RootManager::~RootManager()
{
}

void RootManager::OmniShadowMapPass(PointLight * light)
{
	omniShadowShader.UseShader();

	glViewport(0, 0, light->getShadowMap()->GetShadowWidth(), light->getShadowMap()->GetShadowHeight());

	light->getShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	// uniformModel need to be applied! 
	uniformModel = omniShadowShader.GetModelLocation();

	omniShadowShader.SetVector3("lightPos", light->GetPosition());
	omniShadowShader.SetFloat("farPlane", light->GetFarPlane());
	omniShadowShader.SetLightMatrices(light->CalculateLightTransform());

	NE_ERROR_CHECK(omniShadowShader.Validate());

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RootManager::DirectionalShadowMapPass(DirectionalLight * light)
{
	directionalShadowShader.UseShader();

	glViewport(0, 0, light->getShadowMap()->GetShadowWidth(), light->getShadowMap()->GetShadowHeight());

	light->getShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	// uniformModel need to be applied!
	uniformModel = directionalShadowShader.GetModelLocation();
	directionalShadowShader.SetDirectionalLightTransform(&light->CalculateLightTransform());

	directionalShadowShader.Validate();

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RootManager::RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, PointLight* pointLights, 
	SpotLight* spotLights, int pointlightCount, int spotlightCount)
{
	glViewport(0, 0, renderWindow.GetWindowWidth(), renderWindow.GetWindowHeight());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkybox(viewMatrix, projectionMatrix);

	shaderList[0].UseShader();

	// Upload matrices
	shaderList[0].SetMatrix("projection", projectionMatrix);
	shaderList[0].SetMatrix("view", viewMatrix);
	shaderList[0].SetVector3("eyePosition", camera.GetCameraPosition());

	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointlightCount, 4, 0);
	shaderList[0].SetSpotLights(spotLights, spotlightCount, 4 + pointlightCount, pointlightCount);
	shaderList[0].SetDirectionalLightTransform(&mainLight.CalculateLightTransform());

	mainLight.getShadowMap()->Read(GL_TEXTURE3);
	// Diffuse Texture
	shaderList[0].SetTexture("dTexture", 1);
	// Normal Texture
	shaderList[0].SetTexture("nTexture", 2);
	shaderList[0].SetDirectionalShadowMap(3);

	NE_ERROR_CHECK(shaderList[0].Validate());
}
