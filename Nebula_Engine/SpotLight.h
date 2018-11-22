#pragma once
#include "PointLight.h"
class SpotLight :
	public PointLight
{
public:
	// Create spotlight, dont use directly
	SpotLight();
	// Create spotlight
	SpotLight(unsigned int shadowWidth, unsigned int shadowHeight,
		float near, float far, 
		float red, float green, float blue,
		float aIntensity, float dIntensity,
		float xPos, float yPos, float zPos,
		float xDir, float yDir, float zDir,
		float con, float lin, float exp,
		float edg);

	// Use light
	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
		unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int directionLocation,
		unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation,
		unsigned int edgeLocation);

	// Change position and direction
	void SetFlash(glm::vec3 pos, glm::vec3 dir);

	// Change position
	void SetPosition(glm::vec3 pos);
	// Change direction
	void SetDirection(glm::vec3 dir);

	// Turn light on or off
	void Toggle();

	~SpotLight();

private:
	glm::vec3 direction;

	float edge, procEdge;

	bool isOn;
};

