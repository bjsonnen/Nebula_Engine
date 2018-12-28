#include "main.h"

// math
const float toRadians = 3.14159265f / 180.0f;

// settings
bool loading = true;
float tmp = 0.0f;
bool hdr = true;
bool hdrKeyPressed = false;
float exposure = 1.0f;

glm::mat4 projection;

float deltaTime = 0.0f;
float lastTime = 0.0f;

float blackhawkAngle = 0.0f;

// Compile all shaders & add to list
void CompileShaders()
{
	// Basic shader
	Shader *shader1 = new Shader();
	NE_ERROR_CHECK(shader1->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag"));
	shaderList.push_back(*shader1);

	// Used for the loading screen logo
	shader2 = new Shader();
	NE_ERROR_CHECK(shader2->CreateFromFiles("Shaders/logo.vert", "Shaders/logo.frag"));

	// HDR shader
	screen = new Shader();
	NE_ERROR_CHECK(screen->CreateFromFiles("Shaders/screen.vert", "Shaders/screen.frag"));

	// Directional & omnidirectional shaders
	NE_ERROR_CHECK(directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag"));
	NE_ERROR_CHECK(omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag"));
}

// Render all objects
void RenderScene()
{
	glm::mat4 model;

	// Renderer for old objects
	for (auto& m : modelList)
	{
		model = glm::mat4();
		model = glm::translate(model, m->GetPosition());
		model = glm::rotate(model, Math::ToRadians(m->GetDegrees()), m->GetRotation());
		model = glm::scale(model, m->GetScale());
		shaderList[0].SetBool("renderNormalMaps", m->GetRenderNormalMaps());
		shaderList[0].SetMatrix("model", model);
		if(uniformModel != 0)
			glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(model));
		defaultMaterial.UseMaterial(&shaderList[0]);
		m->RenderModel();
	}

	// Renderer for new objects
	for (auto& e : entityList)
	{
		model = glm::mat4();
		model = glm::translate(model, e->GetComponent<Transform>().GetPosition());
		model = glm::rotate(model, Math::ToRadians(e->GetComponent<Transform>().GetDegrees()), e->GetComponent<Transform>().GetRotation());
		model = glm::scale(model, e->GetComponent<Transform>().GetScale());
		shaderList[0].SetMatrix("model", model);
		if(uniformModel != 0)
			glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(model));
		defaultMaterial.UseMaterial(&shaderList[0]);
		NE_ERROR_CHECK(e->GetComponent<Object>().RenderModel());
	}

	uniformModel = 0;
}

void DirectionalShadowMapPass(DirectionalLight* light)
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

void OmniShadowMapPass(PointLight* light)
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

// Upload uniform variables
void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
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
	shaderList[0].SetPointLights(pointLights, pointLightCount, 4, 0);
	shaderList[0].SetSpotLights(spotLights, spotLightCount, 4 + pointLightCount, pointLightCount);
	shaderList[0].SetDirectionalLightTransform(&mainLight.CalculateLightTransform());

	mainLight.getShadowMap()->Read(GL_TEXTURE3);
	// Diffuse Texture
	shaderList[0].SetTexture("dTexture", 1);
	// Normal Texture
	shaderList[0].SetTexture("nTexture", 2);
	shaderList[0].SetDirectionalShadowMap(3);

	NE_ERROR_CHECK(shaderList[0].Validate());

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
		NE_ERROR_CHECK(textureList[i]->LoadTexture());
	}

	// Load mesh data & textures into ram
	for (int i = 0; i < modelList.size(); i++)
	{
		NE_ERROR_CHECK(modelList[i]->LoadModel());
	}
	for (int i = 0; i < entityList.size(); i++)
	{
		NE_ERROR_CHECK(entityList[i]->GetComponent<Object>().LoadModel());
	}

	// Loading screen finished
	loading = false;
}

int main() 
{
	renderWindow = Window(1280, 720);
	NE_ERROR_CHECK(renderWindow.Initialise());

	EngineInitialization();

	float cooldown = 0.0f;

	// Define Textures
	// => Model load all Textures automaticly
	devTexture = Texture("Textures/dev.jpg");
	textureList.push_back(&devTexture);
	nebulaLogo = Texture("Textures/dev.jpg");

	// Define Models
	CreateLogo();

	float tmp = 0.0f;

	Start();

	testUi = Ui(&renderWindow);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfw_InitForOpenGL(renderWindow.GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImGui::StyleColorsDark();

	bool show_demo_window = true;
	bool show_another_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	NE_ERROR_CHECK(nebulaLogo.LoadTexture());

	while (!renderWindow.GetShouldClose())
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Loading screen image
		if (loading) // NOT WORKING
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// ToDo
			shader2->UseShader();

			tmp += renderWindow.GetDeltaTime();

			glm::mat4 model = glm::mat4();

			model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -2.0f));

			shader2->SetMatrix("projection", projection);
			shader2->SetMatrix("view", camera.CalculateViewMatrix());
			shader2->SetMatrix("model", model);

			shader2->SetTexture("sTexture", 0);

			nebulaLogo.UseTexture(GL_TEXTURE0);
			NebulaEngineLogo.RenderMesh();

			renderWindow.SwapBuffers();
		}

		renderWindow.WindowUpdate();

		renderWindow.SetVSync(false);

		// => Load Data
		if (!loading)
		{
			// Camera update
			camera.KeyControl(renderWindow.GetWindow(), renderWindow.GetDeltaTime());
			camera.MouseControl(renderWindow.GetXChange(), renderWindow.GetYChange());
			
			// Debug Window
			testUi.DebugWindow(true, renderWindow.GetFPS(), renderWindow.GetDeltaTime());

			// Disable movement when mouse is over ui
			//if (testUi.MouseOverUi())
			//{
			//	camera.DisableMouseMovement(true);
			//	camera.DisableKeyMovement(true);
			//}
			//else
			//{
			//	camera.DisableMouseMovement(false);
			//	camera.DisableKeyMovement(false);
			//}

			// User Update
			manager.Update();
			Update();
		}
		else
			// Load all data
			LoadData();
		
		DirectionalShadowMapPass(&mainLight);

		for (int i = 0; i < pointLightCount; i++)
		{
			OmniShadowMapPass(&pointLights[i]);
		}

		for (int i = 0; i < spotLightCount; i++)
		{
			OmniShadowMapPass(&spotLights[i]);
		}

		RenderPass(camera.CalculateViewMatrix(), projection);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		renderWindow.SwapBuffers();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

void EngineInitialization()
{
	CompileShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	defaultMaterial = Material(1.0f, 4);
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

	projection = renderWindow.CalculateProjectionMatrix(glm::radians(60.0f), (float)renderWindow.GetBufferWidth() / renderWindow.GetBufferHeight(), camera.GetNear(), camera.GetFar());
}

int vert = 0;
float tmpRotation = 0;
int multi = 10;

GameObject go1;
GameObject go2;
GameObject go3;
Object testObject;
Audio mainAudio = Audio("Audio/ps2.ogg");

Entity& newPlayer(manager.AddEntity());
Entity& secondPlayer(manager.AddEntity());

void Start()
{
	//newPlayer.AddComponent<Object>();
	//newPlayer.AddComponent<Transform>();
	//newPlayer.AddComponent<Audio>();
	//newPlayer.GetComponent<Object>().SetFileLocation("Models/cube.obj");
	//newPlayer.GetComponent<Transform>().SetPosition(15.0f, 0.0f, 0.0f);
	//entityList.push_back(&newPlayer);

	//secondPlayer.AddComponent<Object>();
	//secondPlayer.AddComponent<Transform>();
	//secondPlayer.GetComponent<Object>().SetFileLocation("Models/cube.obj");
	//secondPlayer.GetComponent<Transform>().SetPosition(-15.0f, 0.0f, 0.0f);
	//entityList.push_back(&secondPlayer);

	go = GameObject("Models/ALucy.fbx");
	go.SetScale(glm::vec3(0.00006f, 0.00006f, 0.00006f));
	modelList.push_back(&go);

	go1 = GameObject("Models/cube.obj");
	go1.SetPosition(0.0f, -5.35f, 0.0f);
	go1.SetScale(10.0f, 1.0f, 10.0f);
	modelList.push_back(&go1);

	go2 = GameObject("Models/cube.obj");
	go2.SetPosition(0.0f, -15.0f, 0.0f);
	go2.SetScale(40.0f, 1.0f, 40.0f);
	modelList.push_back(&go2);

	go3 = GameObject("Models/cube.obj");
	go3.SetPosition(15.0f, 0.0f, 0.0f);
	go3.SetDefaultTexture("Textures/Unbenannt-1.png");
	modelList.push_back(&go3);

	//testObject = Object("Models/ALucy.fbx");
	//testObject.SetScale(glm::vec3(0.00006f, 0.00006f, 0.00006f));
	//testList.push_back(&testObject);
}

void Update()
{
	multi = 10;
	if (vert == 0)
	{
		for (int i = 0; i < modelList.size(); i++)
		{
			vert += modelList[i]->GetVerticesCount();
		}
	}

	//newPlayer.GetComponent<Transform>().SetDegrees(newPlayer.GetComponent<Transform>().GetDegrees() + 1.0f);
	//std::cout << newPlayer.GetComponent<Transform>().GetDegrees() << std::endl;

	if (renderWindow.Key(Window::KeyCode::R))
		multi *= 10;

	tmpRotation += renderWindow.GetDeltaTime() * multi;
	if (tmpRotation >= 360.0f)
		tmpRotation = 0.0f;
	modelList[0]->SetDegrees(tmpRotation);
	modelList[0]->SetRotation(0.0f, -1.0f, 0.0f);

	if (renderWindow.Key(Window::KeyCode::B))
		mainAudio.Play();

	//mainAudio.SetSpeed(2.0f);

	//if (renderWindow.Key(Window::KeyCode::N))
	//	secondAudio.Play();

	//if (renderWindow.Key(Window::KeyCode::T))
	//{
	//	renderWindow.SetWireframe(false);
	//}

	//if (renderWindow.Key(Window::KeyCode::F))
	//{
	//	renderWindow.SetWireframe(true);
	//}

	//if (renderWindow.Key(Window::KeyCode::C))
	//	camera.DisableMouseMovement(true);

	//mainLight.ChangeDirection(glm::vec3(20.0f, 20.0f, 20.0f));

	//renderWindow.SetTitle("Nebula Engine // FPS: " + std::to_string(renderWindow.GetFPS()) + " // Vertices: " + std::to_string(vert));
}

void LinesTest()
{
}
