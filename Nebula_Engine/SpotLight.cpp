#include "SpotLight.h"



SpotLight::SpotLight() : PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	procEdge = cosf(glm::radians(edge));
	isOn = true;
}

SpotLight::SpotLight(unsigned int shadowWidth, unsigned int shadowHeight,
	float near, float far, 
	float red, float green, float blue,
	float aIntensity, float dIntensity, 
	float xPos, float yPos, float zPos, 
	float xDir, float yDir, float zDir, 
	float con, float lin, float exp, 
	float edg) : PointLight(shadowWidth, shadowHeight, near, far, red, green, blue, aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp)
{
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir));

	edge = edg;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation, 
	unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int directionLocation, 
	unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation, 
	unsigned int edgeLocation)
{
	glUniform3f(ambientColourLocation, color.x, color.y, color.z);

	if (isOn)
	{
		glUniform1f(ambientIntensityLocation, ambientIntensity);
		glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	}
	else {
		glUniform1f(ambientIntensityLocation, 0.0f);
		glUniform1f(diffuseIntensityLocation, 0.0f);
	}

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}

void SpotLight::SetFlash(Vector3 pos, Vector3 dir)
{
	position = pos.ToGlm();
	direction = dir.ToGlm();
}

void SpotLight::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void SpotLight::SetPosition(Vector3 pos)
{
	position = pos.ToGlm();
}

void SpotLight::SetDirection(glm::vec3 dir)
{
	direction = dir;
}

void SpotLight::SetDirection(Vector3 dir)
{
	direction = dir.ToGlm();
}

void SpotLight::SetColor(glm::vec3 color)
{
	this->color = color;
}

void SpotLight::SetColor(Vector3 color)
{
	this->color = color.ToGlm();
}

void SpotLight::Toggle()
{
	isOn = !isOn;
}

SpotLight::~SpotLight()
{
}
