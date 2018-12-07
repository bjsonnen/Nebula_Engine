#pragma once

#define STB_IMAGE_IMPLEMENTATION

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
#include "Math.h"
#include "GameObject.h"
#include "Skybox.h"

// uniform variables
unsigned int uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0,
uniformDirectionalLightTransform = 0, uniformOmniLightPos = 0, uniformFarPlane = 0;

// lists
std::vector<Mesh*> meshList;
std::vector<GameObject*> modelList;
std::vector<Texture*> textureList;
std::vector<Shader> shaderList;

// objects
Window renderWindow;

Shader directionalShadowShader;
Shader omniShadowShader;

Camera camera;

Shader* shader2;
Shader* screen;

Texture devTexture;
Texture nebulaLogo;
Texture normal;

Material defaultMaterial;
Material dullMaterial;

GameObject go;
GameObject* test;

Mesh NebulaEngineLogo;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

Skybox skybox;

Audio secondAudio = Audio("trump.mp3");

Util util;

// variables
unsigned int pointLightCount = 0;
unsigned int spotLightCount = 0;

void Start();
void Update();

void EngineInitialization();
