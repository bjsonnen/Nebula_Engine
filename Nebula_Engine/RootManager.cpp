#include "RootManager.h"

void NE::RootManager::EngineInitialization(NE::Window& window, NE::Camera& cam, NE::Material& mat1, NE::Material& mat2, NE::DirectionalLight& light,
	NE::Skybox& skybox, std::vector<NE::Shader>& shaderList, NE::GameObjectList* queue)
{
	CompileShaders();

	this->queue = queue;

	renderWindow = &window;

	camera = NE::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	mat1 = NE::Material(1.0f, 4);
	defaultMaterial = mat1;
	mat2 = NE::Material(0.3f, 4);

	light = NE::DirectionalLight(2048, 2048,
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
	skybox = NE::Skybox(skyboxFaces);
	this->skybox = skybox;
}

void NE::RootManager::EngineUpdate(NE::Camera& cam, NE::DirectionalLight* mainLight)
{
	DirectionalShadowMapPass(mainLight);
	
	for (int i = 0; i < pointCount; i++)
	{
		OmniShadowMapPass(&pointLights[i]);
	}

	for (int i = 0; i < spotsCount; i++)
	{
		OmniShadowMapPass(&spotLights[i]);
	}
	
	RenderPass(this->camera.CalculateViewMatrix(), projection, pointLights, spotLights, pointCount, spotsCount);
	RenderScene();
}

void NE::RootManager::EngineLoading()
{
	for (int i = 0; i < this->textureList->size(); i++)
	{
		NE_ERROR_CHECK(this->textureList->at(i)->LoadTexture());
	}

	for (int i = 0; i < queue->GetSize(); i++)
	{
		if (queue->FindAtIndex(i) != nullptr);
			NE_ERROR_CHECK(queue->FindAtIndex(i)->LoadModel());
	}

	this->loading = false;
}

void NE::RootManager::EngineVariablesUpdate(std::vector<NE::Texture*>* textureList,
	glm::mat4 projection, NE::PointLight* points, NE::SpotLight* spots, unsigned int pointsCount,
	unsigned int spotsCount)
{
	this->textureList = textureList;
	this->pointCount = pointsCount;
	this->projection = projection;
	this->spotsCount = spotsCount;
	this->points = points;
	this->spots = spots;
}

bool NE::RootManager::MainLoop(bool windowShouldClose, NE::Window& window, void* Start, void* Update)
{
	if (firstStart)
	{
		debugWindow = NE::Ui(renderWindow);
		// Manager for the entity-component-system
		manager = new Manager();

		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); 
			(void)io;

			ImGui_ImplGlfw_InitForOpenGL(renderWindow->GetWindow(), true);
			ImGui_ImplOpenGL3_Init("#version 330");

			ImGui::StyleColorsDark();
		}

		((void(*)(void))Start)();

		firstStart = false;
	}
	else
	{
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		// Loading
		if (loading)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			window.SwapBuffers();

			EngineLoading();
		}

		{
			window.WindowUpdate();
			window.SetVSync(false);

			camera.KeyControl(window.GetWindow(), window.GetDeltaTime());
			camera.MouseControl(window.GetXChange(), window.GetYChange());

			debugWindow.DebugWindow(true, renderWindow->GetFPS(), renderWindow->GetDeltaTime());

			// Update
			manager->Update();
			((void(*)(void))Update)();

			CheckForBlendedObjects();

			EngineUpdate(camera, &mainLight);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			window.SwapBuffers();
		}
	}

	return false;
}

void NE::RootManager::CompileCustomShaders(void * custom)
{
	((void(*)(void))custom)();
}

NE_ERROR NE::RootManager::SelectDifferentShader(int i)
{
	if (i >= 0 && i < shaderList.size())
	{
		selectedShader = i;
		return NE_OK;
	}
	return NE_SHADER;
}

void NE::RootManager::ShutDown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void NE::RootManager::RenderScene()
{
	glm::mat4 model;
	glDisable(GL_BLEND);

	for (int i = 0; i < queue->GetSize(); i++)
	{
		model = glm::mat4();
		if (queue->FindAtIndex(i)->GetUseBlending()) // Dont render object with blending
		{
			continue;
		}
		model = glm::translate(model, queue->FindAtIndex(i)->GetPosition());
		model = glm::rotate(model, NE::Mathf::ToRadians(queue->FindAtIndex(i)->GetDegrees()), queue->FindAtIndex(i)->GetRotation());
		model = glm::scale(model, queue->FindAtIndex(i)->GetScale());
		shaderList[selectedShader].SetBool("renderNormalMaps", queue->FindAtIndex(i)->GetRenderNormalMaps());
		shaderList[selectedShader].SetMatrix("model", model);
		shaderList[selectedShader].SetVector3("primaryColor", queue->FindAtIndex(i)->GetMainColor());
		shaderList[selectedShader].SetBool("useNormalMap", queue->FindAtIndex(i)->GetUseNormalMaps());
		if (uniformModel != 0)
			glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(model));
		defaultMaterial.UseMaterial(&shaderList[0]);
		queue->FindAtIndex(i)->RenderModel();
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (std::map<float, NE::GameObject*>::reverse_iterator i = blendedObjects.rbegin(); i != blendedObjects.rend(); ++i)
	{
		model = glm::mat4();
		model = glm::translate(model, i->second->GetPosition());
		model = glm::rotate(model, NE::Mathf::ToRadians(i->second->GetDegrees()), i->second->GetRotation());
		model = glm::scale(model, i->second->GetScale());
		shaderList[selectedShader].SetBool("renderNormalMaps", i->second->GetRenderNormalMaps());
		shaderList[selectedShader].SetMatrix("model", model);
		shaderList[selectedShader].SetVector3("primaryColor", i->second->GetMainColor());
		shaderList[selectedShader].SetBool("useNormalMap", i->second->GetUseNormalMaps());
		if (uniformModel != 0)
			glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(model));
		defaultMaterial.UseMaterial(&shaderList[0]);
		i->second->RenderModel();
	}

	glDisable(GL_BLEND);

	uniformModel = 0;
}

void NE::RootManager::CompileShaders()
{
	NE::Shader* shader1 = new NE::Shader();
	NE_ERROR_CHECK(shader1->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag"));
	shaderList.push_back(*shader1);
	
	NE_ERROR_CHECK(directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag"));

	NE_ERROR_CHECK(omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag"));
}

void NE::RootManager::OmniShadowMapPass(NE::PointLight * light)
{
	omniShadowShader.UseShader();

	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
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

void NE::RootManager::DirectionalShadowMapPass(NE::DirectionalLight * light)
{
	directionalShadowShader.UseShader();

	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	// uniformModel need to be applied!
	uniformModel = directionalShadowShader.GetModelLocation();
	directionalShadowShader.SetDirectionalLightTransform(&light->CalculateLightTransform());

	NE_ERROR_CHECK(directionalShadowShader.Validate());

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void NE::RootManager::RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, NE::PointLight* pointLights,
	NE::SpotLight* spotLights, int pointlightCount, int spotlightCount)
{
	glViewport(0, 0, renderWindow->GetWindowWidth(), renderWindow->GetWindowHeight());

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkybox(viewMatrix, projectionMatrix);

	shaderList[selectedShader].UseShader();

	// Upload matrices
	shaderList[selectedShader].SetMatrix("projection", projectionMatrix);
	shaderList[selectedShader].SetMatrix("view", viewMatrix);
	shaderList[selectedShader].SetVector3("eyePosition", camera.GetCameraPosition());

	shaderList[selectedShader].SetDirectionalLight(&mainLight);
	shaderList[selectedShader].SetPointLights(pointLights, pointlightCount, 4, 0);
	shaderList[selectedShader].SetSpotLights(spotLights, spotlightCount, 4 + pointlightCount, pointlightCount);
	shaderList[selectedShader].SetDirectionalLightTransform(&mainLight.CalculateLightTransform());

	mainLight.GetShadowMap()->Read(GL_TEXTURE3);
	// Diffuse Texture
	shaderList[selectedShader].SetTexture("dTexture", 1);
	// Normal Texture
	shaderList[selectedShader].SetTexture("nTexture", 2);
	shaderList[selectedShader].SetDirectionalShadowMap(3);

	NE_ERROR_CHECK(shaderList[selectedShader].Validate());
}

void NE::RootManager::CheckForBlendedObjects()
{
	glm::vec3 camPos = camera.GetCameraPosition();

	blendedObjects.clear();

	for (int i = 0; i < queue->GetSize(); i++)
	{
		if (queue->FindAtIndex(i)->GetUseBlending())
		{
			float distance = glm::length(camPos - queue->FindAtIndex(i)->GetPosition());
			blendedObjects[distance] = queue->FindAtIndex(i);
		}
	}
}
