#pragma once
#include "Light.h"

#include <vector>

#include "OmniShadowMap.h"

//! Main class to create point lights
class PointLight :
	public Light
{
public:
	//! Creates a Point Light with standard parameters
	PointLight();
	//! Create a Point Light with specific parameters
	//! @param shadowWidth Shadow width as unsigned int
	//! @param shadowHeight Shadow height as unsigned int
	//! @param near Near plane as float
	//! @param far Far plane as float
	//! @param red Red value in RGB as float
	//! @param green Green value in RGB as float
	//! @param blue Blue value in RGB as float
	//! @param aIntensity Insert ambient intensity as float
	//! @param dIntensity Insert diffuse intensity as float
	//! @param xPos Insert position X value as float
	//! @param yPos Insert position Y value as float
	//! @param zPos Insert position Z value as float
	PointLight(unsigned int shadowWidth, unsigned int shadowHeight,
		float near, float far,
		float red, float green, float blue,
		float aIntensity, float dIntensity,
		float xPos, float yPos, float zPos,
		float con, float lin, float exp);

	//! Use Light
	//! @param ambientIntensityLocation Insert ambientIntensity location in shader
	//! @param ambientColourLocation Insert ambientColor location in shader
	//! @param diffuseIntensityLocation Insert diffuseIntensity location in shader
	//! @param positionLocation Insert position location in shader
	//! @param constantLocation Insert constant location in shader
	//! @param linearLocation Insert linear location in shader
	//! @param exponentLocation Insert exponent location in shader
	void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
		unsigned int diffuseIntensityLocation, unsigned int positionLocation,
		unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation);

	//! Returns the light transforms
	//! @return Returns light transforms as std::vector<glm::mat4>
	std::vector<glm::mat4> CalculateLightTransform();
	//! Returns current far plane
	//! @return Returns far plane distance as float
	float GetFarPlane();

	//! Set Light Position
	//! @param pos Set position as glm::vec3
	void SetPosition(glm::vec3 pos);
	//! Get Light Position
	//! @return Returns the position as glm::vec3
	glm::vec3 GetPosition();

	//! Use to delete the Light
	~PointLight();

protected:
	glm::vec3 position;

	float constant, linear, exponent;

	float farPlane;
};

