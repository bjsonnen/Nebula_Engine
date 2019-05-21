#include "main.h"

// settings
bool loading = true;
float tmp = 0.0f;
bool hdr = true;
bool hdrKeyPressed = false;
float exposure = 1.0f;

glm::mat4 projection;

float deltaTime = 0.0f;
float lastTime = 0.0f;

int vert = 0;
float tmpRotation = 0;
int multi = 10;

GameObject go1;
GameObject go2;
GameObject go3;
Audio mainAudio = Audio("Audio/ps2.ogg");

float tmpColor;

void Start()
{
	go1 = GameObject("Models/cube.obj");
	go1.SetPosition(0.0f, -5.35f, 0.0f);
	go1.SetScale(10.0f, 1.0f, 10.0f);
	go1.UseBlending(false);
	modelList.push_back(&go1);

	go2 = GameObject("Models/cube.obj");
	go2.SetPosition(0.0f, -15.0f, 0.0f);
	go2.SetScale(40.0f, 1.0f, 40.0f);
	go2.UseNormalMaps(false);
	modelList.push_back(&go2);

	go = GameObject("Models/penguin.obj");
	go.SetPosition(0.0f, 4.0f, 0.0f);
	go.SetRotation(1.0f, 0.0f, 0.0f);
	go.SetScale(0.05f, 0.05f, 0.05f);
	go.SetDegrees(-90.0f);
	go.UseNormalMaps(false);
	modelList.push_back(&go);

	go3 = GameObject("Models/spider.obj");
	go3.SetPosition(0.0f, -5.0f, 0.0f);
	go3.SetScale(0.09f, 0.09f, 0.09f);
	modelList.push_back(&go3);

	blending1 = GameObject("Models/cube.obj");
	blending1.SetPosition(15.0f, 0.0f, 0.0f);
	blending1.SetDefaultTexture("Textures/blending.png");
	blending1.UseNormalMaps(false);
	blending1.UseBlending(true);
	modelList.push_back(&blending1);

	blending2 = GameObject("Models/cube.obj");
	blending2.SetPosition(0.0f, 3.0f, 0.0f);
	blending2.SetDefaultTexture("Textures/blending.png");
	blending2.UseNormalMaps(false);
	blending2.UseBlending(true);
	modelList.push_back(&blending2);

	modelList[1]->ChangeMainColor(ObjectColor::Orange);
}

glm::vec3 tmpcolor = glm::vec3();

void Update()
{
	multi = 10;
	if (renderWindow.Key(Window::KeyCode::R)) multi *= 10;

	tmpRotation += renderWindow.GetDeltaTime() * multi;
	if (tmpRotation >= 360.0f) tmpRotation = 0.0f;
	modelList[0]->SetDegrees(tmpRotation);
	modelList[0]->SetRotation(0.0f, -1.0f, 0.0f);

	if (renderWindow.Key(Window::KeyCode::G))
		mainAudio.Play();

	if (tmpcolor.x > 1.0f) tmpcolor.x = 0.0f; else tmpcolor.x += 0.001f;
	if (tmpcolor.y > 1.0f) tmpcolor.y = 0.0f; else tmpcolor.y += 0.002f;
	if (tmpcolor.z > 1.0f) tmpcolor.z = 0.0f; else tmpcolor.z += 0.003f;
	modelList[1]->ChangeMainColor(tmpcolor);

	if (renderWindow.Key(Window::KeyCode::B))
		mainAudio.Play();
}

// Compile own Shaders 
void CompileShaders()
{
}

int main() 
{
	// Window init
	renderWindow = Window(1280, 720);
	NE_ERROR_CHECK(renderWindow.Initialise());

	// Engine Setup
	rm.EngineInitialization(renderWindow, camera, defaultMaterial, dullMaterial, mainLight, 
		skybox, shaderList);
	rm.CompileCustomShaders(CompileShaders);
	shaderList = rm.GetShaderList();
	camera = rm.GetCamera();
	projection = renderWindow.CalculateProjectionMatrix(glm::radians(60.0f), 
		(float)renderWindow.GetBufferWidth() / renderWindow.GetBufferHeight(), 
		camera.GetNear(), camera.GetFar());

	float cooldown = 0.0f;

	float tmp = 0.0f;

	while (!renderWindow.GetShouldClose())
	{
		rm.EngineVariablesUpdate(&textureList, &modelList, projection, pointLights, spotLights, pointLightCount, spotLightCount);
		rm.MainLoop(renderWindow.GetShouldClose(), renderWindow, Start, Update);
	}

	rm.ShutDown();

	return 0;
}