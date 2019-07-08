#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <stdio.h>

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
#include "GameObject.h"
#include "Skybox.h"
#include "Ui.h"
#include "RootManager.h"
#include "GameObjectList.h"

#include "ECManager.h"
#include "Components.h"

#include "Vector2.h"
#include "Vector3.h"
#include "RootManager.h"

// uniform variables
unsigned int uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0,
uniformDirectionalLightTransform = 0, uniformOmniLightPos = 0, uniformFarPlane = 0;

// lists
std::vector<NE::Mesh*> meshList;
std::vector<NE::Texture*> textureList;
std::vector<NE::Shader> shaderList;

// objects
NE::Window renderWindow;

NE::Shader directionalShadowShader;
NE::Shader omniShadowShader;

NE::GameObjectList queue;

NE::RootManager rm;

NE::Camera camera;

NE::Shader* shader2;
NE::Shader* screen;

NE::Texture devTexture;
NE::Texture nebulaLogo;
NE::Texture normal;

NE::Material defaultMaterial;
NE::Material dullMaterial;

NE::Mesh NebulaEngineLogo;

NE::DirectionalLight mainLight;
NE::PointLight pointLights[MAX_POINT_LIGHTS];
NE::SpotLight spotLights[MAX_SPOT_LIGHTS];

NE::PointLight testPL;
NE::SpotLight testSL;

NE::Skybox skybox;

NE::Audio secondAudio = NE::Audio("trump.mp3");

NE::Util util;

NE::Ui testUi;

// variables
unsigned int pointLightCount = 0;
unsigned int spotLightCount = 0;

void Start();
void Update();