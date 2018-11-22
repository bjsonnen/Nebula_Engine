#pragma once
#include "Light.h"

class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(unsigned int shadowWidth, unsigned int shadowHeight, 
					float red, float green, float blue,
					float aIntensity, float dIntensity,
					float xDir, float yDir, float zDir);

	// Use the current light
	void UseLight(float ambientIntensityLocation, float ambientColourLocation,
		float diffuseIntensityLocation, float directionLocation);

	// Change the direction of the light
	void ChangeDirection(glm::vec3 offset);

	// Set the direction of the light
	void SetDirection(glm::vec3 direction);

	// Get the current direction
	glm::vec3 GetDirection() 
	{
		return direction;
	};

	// Calculate current Light Transform
	glm::mat4 CalculateLightTransform();

	~DirectionalLight();

private:
	glm::vec3 direction;
};

