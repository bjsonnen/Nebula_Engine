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

int vert = 0;
float tmpRotation = 0;
int multi = 10;

GameObject go1;
GameObject go2;
GameObject go3;
Audio mainAudio = Audio("Audio/ps2.ogg");

Entity& firstPlayer(manager.AddEntity());
Entity& secondPlayer(manager.AddEntity());

float tmpColor;

void Start()
{
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

	Vector2 blubb;
	printf("Blubb: %s\n", blubb.ToString());

	modelList[1]->ChangeMainColor(ObjectColor::Orange);
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
}

// Compile own Shaders 
void CompileShaders()
{
	// Used for the loading screen logo
	shader2 = new Shader();
	NE_ERROR_CHECK(shader2->CreateFromFiles("Shaders/logo.vert", "Shaders/logo.frag"));

	// HDR shader
	screen = new Shader();
	NE_ERROR_CHECK(screen->CreateFromFiles("Shaders/screen.vert", "Shaders/screen.frag"));
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

int main() 
{
	renderWindow = Window(1280, 720);
	NE_ERROR_CHECK(renderWindow.Initialise());

	rm.EngineInitialization(renderWindow, camera, defaultMaterial, dullMaterial, mainLight, skybox, shaderList);
	rm.CompileCustomShaders(CompileShaders);

	shaderList = rm.GetShaderList();

	//CompileShaders();
	camera = rm.GetCamera();

	projection = renderWindow.CalculateProjectionMatrix(glm::radians(60.0f), 
		(float)renderWindow.GetBufferWidth() / renderWindow.GetBufferHeight(), 
		camera.GetNear(), camera.GetFar());

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

	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplGlfw_InitForOpenGL(renderWindow.GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 130");

		ImGui::StyleColorsDark();

		bool show_demo_window = true;
		bool show_another_window = true;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	}

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

			// User Update
			manager.Update();
			Update();
		}
		else
			// Load all data
			rm.EngineLoading(&textureList, &modelList, loading);

		rm.EngineUpdate(&modelList, camera, pointLights, 
			spotLights, pointLightCount, spotLightCount, projection, &mainLight);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		renderWindow.SwapBuffers();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}