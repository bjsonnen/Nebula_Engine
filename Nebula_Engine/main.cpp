#include "main.h"

#include "Math.h"

glm::mat4 projection;

NE::GameObject go;
NE::GameObject go1;
NE::GameObject go2;
NE::GameObject go3;
NE::GameObject blending1;
NE::GameObject blending2;
NE::Audio mainAudio = NE::Audio("Audio/ps2.ogg");

NE::Matrix3x3 hallo;

float tmp = 0.0f;
float tmpColor;
float tmpRotation = 0;
int vert = 0;
int multi = 10;

bool loading = true;

void Start()
{
	go1 = NE::GameObject("Models/cube.obj");
	go1.SetPosition(0.0f, -5.35f, 0.0f);
	go1.SetScale(10.0f, 1.0f, 10.0f);
	go1.UseBlending(false);
	modelList.push_back(&go1);
	queue.Add(go1);

	go2 = NE::GameObject("Models/cube.obj");
	go2.SetPosition(0.0f, -15.0f, 0.0f);
	go2.SetScale(40.0f, 1.0f, 40.0f);
	go2.UseNormalMaps(false);
	queue.Add(go2);

	go = NE::GameObject("Models/penguin.obj");
	go.SetPosition(0.0f, 4.0f, 0.0f);
	go.SetRotation(1.0f, 0.0f, 0.0f);
	go.SetScale(0.05f, 0.05f, 0.05f);
	go.SetDegrees(-90.0f);
	go.UseNormalMaps(false);
	queue.Add(go);

	go3 = NE::GameObject("Models/spider.obj");
	go3.SetPosition(0.0f, -5.0f, 0.0f);
	go3.SetScale(0.09f, 0.09f, 0.09f);
	go3.UseBlending(true);
	queue.Add(go3);

	blending1 = NE::GameObject("Models/cube.obj");
	blending1.SetPosition(15.0f, 0.0f, 0.0f);
	blending1.SetDefaultTexture("Textures/blending.png");
	blending1.UseNormalMaps(false);
	blending1.UseBlending(true);
	queue.Add(blending1);

	blending2 = NE::GameObject("Models/cube.obj");
	blending2.SetPosition(0.0f, 3.0f, 0.0f);
	blending2.SetDefaultTexture("Textures/blending.png");
	blending2.UseNormalMaps(false);
	blending2.UseBlending(true);
	queue.Add(blending2);

	// Wrong color multiplication! 
	// Light upload works
	//testPL = NE::PointLight(2048, 2048,
	//	0.1f, 1000.0f, 0.0f, 0.0f, 1.0f,
	//	0.0f, 0.1f,
	//	-4.0f, 2.0f, 0.0f,
	//	0.3f, 0.1f, 0.1f);
	//pointLightCount++;
	//pointLights[0] = testPL;

	go2.ChangeMainColor(NE::ObjectColor::Orange);
}

glm::vec3 tmpcolor = glm::vec3();

void Update()
{
	multi = 10;
	if (renderWindow.Key(NE::Window::KeyCode::R)) multi *= 10;
	tmpRotation += renderWindow.GetDeltaTime() * multi;
	if (tmpRotation >= 360.0f) tmpRotation = 0.0f;

	go1.SetDegrees(tmpRotation);
	go1.SetRotation(0.0f, -1.0f, 0.0f);

	if (renderWindow.Key(NE::Window::KeyCode::G))
		mainAudio.Play();

	if (tmpcolor.x > 1.0f) tmpcolor.x = 0.0f; else tmpcolor.x += 0.001f;
	if (tmpcolor.y > 1.0f) tmpcolor.y = 0.0f; else tmpcolor.y += 0.002f;
	if (tmpcolor.z > 1.0f) tmpcolor.z = 0.0f; else tmpcolor.z += 0.003f;
	//go2.ChangeMainColor(tmpcolor);

	if (renderWindow.Key(NE::Window::KeyCode::B))
		queue.Remove(blending2);

	if(renderWindow.Key(NE::Window::KeyCode::N))
		mainAudio.Play();
}

// Compile own Shaders 
void CompileShaders()
{
}

int main() 
{
	// Window init
	renderWindow = NE::Window(1280, 720);
	NE_ERROR_CHECK(renderWindow.Initialise());

	// Engine Setup
	rm.EngineInitialization(renderWindow, camera, defaultMaterial, dullMaterial, mainLight, 
		skybox, shaderList, &queue);
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
		rm.EngineVariablesUpdate(&textureList, projection, pointLights, spotLights, pointLightCount, spotLightCount);
		rm.MainLoop(renderWindow.GetShouldClose(), renderWindow, Start, Update);
	}

	rm.ShutDown();

	return 0;
}