#pragma once
#include "Light.h"

#include <vector>

#include "OmniShadowMap.h"

class PointLight :
	public Light
{
public:
	PointLight();
	// Create a Point Light
	PointLight(unsigned int shadowWidth, unsigned int shadowHeight,
		float near, float far,
		float red, float green, float blue,
		float aIntensity, float dIntensity,
		float xPos, float yPos, float zPos,
		float con, float lin, float exp);

	// Use Light
	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
		unsigned int diffuseIntensityLocation, unsigned int positionLocation,
		unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation);

	std::vector<glm::mat4> CalculateLightTransform();
	float GetFarPlane();

	// Set Light Position
	void SetPosition(glm::vec3 pos);
	// Get Light Position
	glm::vec3 GetPosition();

	// Use to delete the Light
	~PointLight();

protected:
	glm::vec3 position;

	float constant, linear, exponent;

	float farPlane;
};

