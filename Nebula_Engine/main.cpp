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

//Entity& firstPlayer(manager.AddEntity());
//Entity& secondPlayer(manager.AddEntity());

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
	go2.UseNormalMaps(false);
	modelList.push_back(&go2);

	go3 = GameObject("Models/cube.obj");
	go3.SetPosition(15.0f, 0.0f, 0.0f);
	go3.SetDefaultTexture("Textures/Unbenannt-1.png");
	go3.UseNormalMaps(false);
	modelList.push_back(&go3);

	Vector3 testvector;
	Vector2 testvector2;
	testvector.x = 12.0f;
	testvector.y = 7.0f;
	testvector.z = 3.0f;

	testvector2.x = 30.0f;
	testvector2.y = 15.0f;

	PointLight test;
	test.SetPosition(glm::vec3(-2.0f, 2.0f, -2.0f));

	NE_DEBUG_LOG(testvector);
	NE_DEBUG_LOG(testvector2);

	modelList[1]->ChangeMainColor(ObjectColor::Orange);
}

glm::vec3 tmpcolor = glm::vec3();

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

	tmpcolor.x += 0.001f;
	tmpcolor.y += 0.002f;
	tmpcolor.z += 0.003f;
	if (tmpcolor.x > 1.0f) tmpcolor.x = 0.0f;
	if (tmpcolor.y > 1.0f) tmpcolor.y = 0.0f;
	if (tmpcolor.z > 1.0f) tmpcolor.z = 0.0f;
	modelList[1]->ChangeMainColor(tmpcolor);

	if (renderWindow.Key(Window::KeyCode::B))
		mainAudio.Play();
}

// Compile own Shaders 
void CompileShaders()
{
	// HDR shader
	screen = new Shader();
	NE_ERROR_CHECK(screen->CreateFromFiles("Shaders/screen.vert", "Shaders/screen.frag"));
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

	devTexture = Texture("Textures/dev.jpg");
	textureList.push_back(&devTexture);

	float tmp = 0.0f;

	//NE_ERROR_CHECK(nebulaLogo.LoadTexture());

	while (!renderWindow.GetShouldClose())
	{
		rm.EngineVariablesUpdate(&textureList, &modelList, projection, pointLights, spotLights, pointLightCount, spotLightCount);
		rm.MainLoop(renderWindow.GetShouldClose(), renderWindow, Start, Update);
	}

	rm.ShutDown();

	return 0;
}