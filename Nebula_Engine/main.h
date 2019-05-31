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
std::vector<Mesh*> meshList;
std::vector<GameObject*> modelList;
std::vector<Object*> testList;
std::vector<Texture*> textureList;
std::vector<Shader> shaderList;
std::vector<Entity*> entityList;

std::vector<GameObject> objectList;

// objects
Window renderWindow;

Shader directionalShadowShader;
Shader omniShadowShader;

GameObjectList queue;

RootManager rm;

Camera camera;

Shader* shader2;
Shader* screen;

Texture devTexture;
Texture nebulaLogo;
Texture normal;

Material defaultMaterial;
Material dullMaterial;

GameObject go;
GameObject blending1;
GameObject blending2;
GameObject* test;

Mesh NebulaEngineLogo;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

PointLight testPL;
SpotLight testSL;

Skybox skybox;

Audio secondAudio = Audio("trump.mp3");

Util util;

Ui testUi;

// variables
unsigned int pointLightCount = 0;
unsigned int spotLightCount = 0;

void Start();
void Update();