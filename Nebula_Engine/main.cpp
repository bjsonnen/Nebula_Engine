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
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles("Shaders/shader.vert", "Shaders/shader.frag");
	shaderList.push_back(*shader1);

	shader2 = new Shader();
	shader2->CreateFromFiles("Shaders/logo.vert", "Shaders/logo.frag");

	screen = new Shader();
	screen->CreateFromFiles("Shaders/screen.vert", "Shaders/screen.frag");

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
		model = glm::translate(model, modelList[i]->GetPosition());
		model = glm::rotate(model, modelList[i]->GetDegrees() * toRadians, modelList[i]->GetRotation());
		model = glm::scale(model, modelList[i]->GetScale());
		shaderList[0].SetMatrix("model", model);
		if (uniformModel != 0)
			glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(model));
		defaultMaterial.UseMaterial(&shaderList[0]);
		modelList[i]->RenderModel();
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

	// Upload matrices
	shaderList[0].SetMatrix("projection", projectionMatrix);
	shaderList[0].SetMatrix("view", viewMatrix);
	shaderList[0].SetVector3("eyePosition", camera.GetCameraPosition());

	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointLightCount, 4, 0);
	shaderList[0].SetSpotLights(spotLights, spotLightCount, 4 + pointLightCount, pointLightCount);
	shaderList[0].SetDirectionalLightTransform(&mainLight.CalculateLightTransform());

	mainLight.getShadowMap()->Read(GL_TEXTURE3);
	shaderList[0].SetTexture("dTexture", 1);
	shaderList[0].SetTexture("nTexture", 2);
	shaderList[0].SetDirectionalShadowMap(3);

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

	nebulaLogo.LoadTexture();

	while (!renderWindow.GetShouldClose())
	{
		// Loading screen image
		if (loading) // NOT WORKING
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// ToDo
			shader2->UseShader();

			tmp += renderWindow.GetDeltaTime();

			glm::mat4 model = glm::mat4();

			shader2->SetMatrix("projection", projection);
			shader2->SetMatrix("view", camera.CalculateViewMatrix());
			shader2->SetMatrix("model", model);

			shader2->SetTexture("sTexture", 0);

			nebulaLogo.UseTexture(GL_TEXTURE0);
			NebulaEngineLogo.RenderMesh();

			renderWindow.SwapBuffers();
		}

		renderWindow.WindowUpdate();

		// => Load Data
		if (!loading)
		{
			// Camera update
			camera.KeyControl(renderWindow.GetWindow(), renderWindow.GetDeltaTime());
			camera.MouseControl(renderWindow.GetXChange(), renderWindow.GetYChange());

			// Post Processing
			//pp.StartParsing();
			Update();
		}
		else
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
		
		//pp.EndParsing(test); // Display Post Processing

		renderWindow.SwapBuffers();
	}

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

	//projection = glm::perspective(glm::radians(60.0f), (float)renderWindow.GetBufferWidth() / renderWindow.GetBufferHeight(), camera.GetNear(), camera.GetFar());
	projection = renderWindow.CalculateProjectionMatrix(glm::radians(60.0f), (float)renderWindow.GetBufferWidth() / renderWindow.GetBufferHeight(), camera.GetNear(), camera.GetFar());
}

int vert = 0;
float tmpRotation = 0;
int multi = 10;

GameObject go1;
GameObject go2;
GameObject go3;
Audio mainAudio = Audio("Audio/ps2.ogg");

void Start()
{
	renderWindow.SetWireframe(false);

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
	go3.SetPosition(10.0f, 10.0f, 10.0f);
	go3.SetDefaultTexture("Textures/Unbekannt-1.png");
	modelList.push_back(&go3);

	renderWindow.SetRefreshRate(30);
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

	if (renderWindow.Key(Window::KeyCode::R))
		multi *= 10;

	tmpRotation += renderWindow.GetDeltaTime() * multi;
	if (tmpRotation >= 360.0f)
		tmpRotation = 0.0f;
	modelList[0]->SetDegrees(tmpRotation);
	modelList[0]->SetRotation(0.0f, -1.0f, 0.0f);

	if (renderWindow.Key(Window::KeyCode::B))
		mainAudio.Play();

	if (renderWindow.Key(Window::KeyCode::N))
		secondAudio.Play();

	if (renderWindow.Key(Window::KeyCode::T))
	{
		renderWindow.SetWireframe(false);
	}

	if (renderWindow.Key(Window::KeyCode::F))
	{
		renderWindow.SetWireframe(true);
	}

	//mainLight.ChangeDirection(glm::vec3(20.0f, 20.0f, 20.0f));

	renderWindow.SetTitle("Nebula Engine // FPS: " + std::to_string(renderWindow.GetFPS()) + " // Vertices: " + std::to_string(vert));
}