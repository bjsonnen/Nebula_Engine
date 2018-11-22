#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "CommonValues.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader
{
public:
	Shader();
	Shader(std::string vertex, std::string geometry, std::string fragment);

	// Create Shader from string
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	// Create Shader from file
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	// Create from file with geometry shader
	void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);

	// Check if shader works
	void Validate();

	// Read shader from file
	std::string ReadFile(const char* fileLocation);

	// Get Location in shader on the gpu
	unsigned int GetProjectionLocation();
	// Get Location in shader on the gpu
	unsigned int GetModelLocation();
	// Get Location in shader on the gpu
	unsigned int GetViewLocation();
	// Get Location in shader on the gpu
	unsigned int GetAmbientIntensityLocation();
	// Get Location in shader on the gpu
	unsigned int GetAmbientColourLocation();
	// Get Location in shader on the gpu
	unsigned int GetDiffuseIntensityLocation();
	// Get Location in shader on the gpu
	unsigned int GetDirectionLocation();
	// Get Location in shader on the gpu
	unsigned int GetSpecularIntensityLocation();
	// Get Location in shader on the gpu
	unsigned int GetShininessLocation();
	// Get Location in shader on the gpu
	unsigned int GetEyePositionLocation();
	// Get Location in shader on the gpu
	unsigned int GetOmniLightPosLocation();
	// Get Location in shader on the gpu
	unsigned int GetFarPlaneLocation();

	void SetDirectionalLight(DirectionalLight * dLight);
	void SetPointLights(PointLight * pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void SetSpotLights(SpotLight * sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void SetTexture(unsigned int textureUnit);
	void SetNormal(unsigned int normalUnit);
	void SetDirectionalShadowMap(unsigned int textureUnit);
	void SetDirectionalLightTransform(glm::mat4* lTransform);
	void SetLightMatrices(std::vector<glm::mat4> lightMatrices);

	// Set float in shader
	void SetFloat(std::string name, float value);
	// Set int in shader
	void SetInt(std::string name, int value);
	// Set double in shader
	void SetDouble(std::string name, double value);
	// Set bool in shader
	void SetBool(std::string name, bool value);
	// Set texture in shader
	void SetTexture(std::string name, unsigned int unit);
	// Set vector3 in shader
	void SetVector3(std::string name, glm::vec3 value);
	// Set vector2 in shader
	void SetVector2(std::string name, glm::vec2 value);
	// Set 4x4 matrix in shader
	void SetMatrix(std::string name, glm::mat4 value);

	// Use Shader
	void UseShader();
	// Delete Shader
	// => Dont forget to delete it from shaderList
	void ClearShader();

	~Shader();

private:
	// Compile vertex & fragment(pixel) shader
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	// Compile vertex, geometry & fragment(pixel) shader
	void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
	void AddShader(unsigned int theProgram, const char* shaderCode, GLenum shaderType);

	void CompileProgram();

private:
	int pointLightCount;
	int spotLightCount;

	// Varibles used to upload uniform buffers
	unsigned int shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformSpecularIntensity, uniformShininess, 
		uniformTexture, uniformDirectionalShadowMap, 
		uniformDirectionalLightTransform,
		uniformOmniLightPos, uniformFarPlane;
	
	unsigned int uniformLightMatrices[6];

	struct {
		unsigned int uniformColor;
		unsigned int uniformAmbientIntensity;
		unsigned int uniformDiffuseIntensity;

		unsigned int uniformDirection;
	} uniformDirectionalLight;

	unsigned int uniformPointLightCount;

	struct {
		unsigned int uniformColor;
		unsigned int uniformAmbientIntensity;
		unsigned int uniformDiffuseIntensity;

		unsigned int uniformPosition;
		unsigned int uniformConstant;
		unsigned int uniformLinear;
		unsigned int uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	unsigned int uniformSpotLightCount;

	struct 
	{
		unsigned int uniformColor;
		unsigned int uniformAmbientIntensity;
		unsigned int uniformDiffuseIntensity;

		unsigned int uniformPosition;
		unsigned int uniformConstant;
		unsigned int uniformLinear;
		unsigned int uniformExponent;

		unsigned int uniformDirection;
		unsigned int uniformEdge;
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	struct {
		unsigned int shadowMap;
		unsigned int farPlane;
	} uniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];


	std::string vertexShader, geometryShader, fragmentShader;

	unsigned int uniformNormalTexture;
};

