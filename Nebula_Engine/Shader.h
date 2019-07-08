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
#include "Util.h"

#include "Math.h"

namespace NE
{
	//! Main shader class, create new shaders via Shader.CreateFromFiles() / CreateFromString()
	class Shader
	{
	public:
		//! Create a shader with standard parameters
		Shader();
		//! Create a shader with specific parameters
		//! @param vertex File location to the vertex shader as std::string
		//! @param geometry File location to the geometry shader as std::string
		//! @param fragment File location to the fragment shader as std::string
		Shader(std::string vertex, std::string geometry, std::string fragment);

		//! Create Shader from string
		//! @param vertexCode Insert const char array to vertex shader code
		//! @param vertexCode Insert const char array to vertex shader code
		//! @return Returns a NE_ERROR
		//! @see NE_ERROR_CHECK
		NE_ERROR CreateFromString(const char* vertexCode, const char* fragmentCode);
		//! Create Shader from file
		//! @param vertexLocation Insert const char array to vertex file location
		//! @param fragmentLocation Insert const char array to fragment file location
		//! @return Returns a NE_ERROR
		//! @see NE_ERROR_CHECK
		NE_ERROR CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
		//! Create from file with geometry shader
		//! @param vertexLocation Insert const char array to vertex file location
		//! @param geometryLocation Insert const char array to geometry file location
		//! @param fragmentLocation Insert const char array to fragment file location
		//! @return Returns a NE_ERROR
		//! @see NE_ERROR_CHECK
		NE_ERROR CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);

		//! Check if shader works
		//! @return Returns a NE_ERROR
		//! @see NE_ERROR_CHECK
		NE_ERROR Validate();

		//! Read shader from file
		//! @param fileLocation Insert const char array as file location
		//! @return Returns a std::string
		std::string ReadFile(const char* fileLocation);

		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetProjectionLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetModelLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetViewLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetAmbientIntensityLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetAmbientColorLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetDiffuseIntensityLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetDirectionLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetSpecularIntensityLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetShininessLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetEyePositionLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetOmniLightPosLocation();
		//! Get Location in shader on the gpu
		//! @return Returns an unsigned int to the shader location
		unsigned int GetFarPlaneLocation();

		//! Set directional light in selected shader
		//! @param dLight Insert directional light as DirectionalLight*
		//! @see DirectionalLight
		void SetDirectionalLight(DirectionalLight * dLight);
		//! Set point lights in selected shader
		//! @param pLight Insert point light array as PointLight*
		//! @param iightCount Insert light count of elements in the array as unsigned int
		//! @param textureUnit Insert texture unit id from shader as unsigned int
		//! @param offset Insert offset of elements as unsigned int
		//! @see PointLight
		void SetPointLights(PointLight * pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
		//! Set spot lights in selected shader
		//! @param sLight Insert spot light array as SpotLight*
		//! @param iightCount Insert light count of elements in the array as unsigned int
		//! @param textureUnit Insert texture unit id from shader as unsigned int
		//! @param offset Insert offset of elements as unsigned int
		//! @see SpotLight
		void SetSpotLights(SpotLight * sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
		//! Set texture in selected shader
		//! @param textureUnit Insert texture unit from shader as unsigned int
		void SetTexture(unsigned int textureUnit);
		//! Set normal texture in selected shader
		//! @param normalUnit Insert normal texture unit from shader as unsigned int
		void SetNormal(unsigned int normalUnit);
		//! Set directional shadow map in selected shader
		//! @param textureUnit Insert texture unit id from shader as unsigned int
		void SetDirectionalShadowMap(unsigned int textureUnit);
		//! Set directional shadow maps in selected shader
		//! @param lTransform Insert 4x4 matrix as glm::mat4
		void SetDirectionalLightTransform(glm::mat4* lTransform);
		//! Set light matrices in selected shader
		//! @param lightMatrices Insert std::vector of lightMatrices as std::vector<glm::mat4>
		void SetLightMatrices(std::vector<glm::mat4> lightMatrices);

		//! Set float in shader
		//! @param name Insert name in shader as std::string
		//! @param value Insert value for 'name' in shader as float
		void SetFloat(std::string name, float value);
		//! Set int in shader
		//! @param name Insert name in shader as std::string
		//! @param value Insert value for 'name' in shader as int
		void SetInt(std::string name, int value);
		//! Set double in shader
		//! @param name Insert name in shader as std::string
		//! @param value Insert value for 'name' in shader as double
		void SetDouble(std::string name, double value);
		//! Set bool in shader
		//! @param name Insert name in shader as std::string
		//! @param value Insert value for 'name' in shader as bool
		void SetBool(std::string name, bool value);
		//! Set texture in shader
		void SetTexture(std::string name, unsigned int unit);
		//! Set vector4 in shader
		//! @param name Insert name in shader as std::string
		//! @param value Insert value for 'name' in shader as glm::vec3
		void SetVector4(std::string name, glm::vec4 value);
		//! Set vector3 in shader
		//! @param name Insert name in shader as std::string
		//! @param value Insert value for 'name' in shader as glm::vec3
		void SetVector3(std::string name, glm::vec3 value);
		//! Set vector2 in shader
		//! @param name Insert name in shader as std::string
		//! @param value Insert value for 'name' in shader as glm::vec2
		void SetVector2(std::string name, glm::vec2 value);
		//! Set 4x4 matrix in shader
		//! @param name Insert name in shader as std::string
		//! @param value Insert value for 'name' in shader as glm::mat4
		void SetMatrix(std::string name, glm::mat4 value);

		//! Use Shader
		//! 
		void UseShader();
		//! Delete Shader
		//! Dont forget to delete it from shaderList
		void ClearShader();

		~Shader();

	private:
		//! Compile vertex & fragment(pixel) shader
		NE_ERROR CompileShader(const char* vertexCode, const char* fragmentCode);
		//! Compile vertex, geometry & fragment(pixel) shader
		NE_ERROR CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
		NE_ERROR AddShader(unsigned int theProgram, const char* shaderCode, unsigned int shaderType);

		void CompileProgram();

	private:
		int pointLightCount;
		int spotLightCount;

		//! Varibles used to upload uniform buffers
		unsigned int shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
			uniformSpecularIntensity, uniformShininess,
			uniformTexture, uniformDirectionalShadowMap,
			uniformDirectionalLightTransform,
			uniformOmniLightPos, uniformFarPlane;

		unsigned int uniformLightMatrices[6];

		struct 
		{
			unsigned int uniformColor;
			unsigned int uniformAmbientIntensity;
			unsigned int uniformDiffuseIntensity;

			unsigned int uniformDirection;
		} uniformDirectionalLight;

		unsigned int uniformPointLightCount;

		struct 
		{
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

		struct 
		{
			unsigned int shadowMap;
			unsigned int farPlane;
		} uniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];


		std::string vertexShader, geometryShader, fragmentShader;

		unsigned int uniformNormalTexture;
	};


}