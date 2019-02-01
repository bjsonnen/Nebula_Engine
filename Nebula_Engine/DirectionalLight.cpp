#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(unsigned int shadowWidth, unsigned int shadowHeight, 
									float red, float green, float blue,
									float aIntensity, float dIntensity,
									float xDir, float yDir, float zDir) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);

	lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void DirectionalLight::UseLight(float ambientIntensityLocation, float ambientColourLocation,
	float diffuseIntensityLocation, float directionLocation)
{
	glUniform3f(ambientColourLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

void DirectionalLight::ChangeDirection(glm::vec3 offset)
{
	direction += offset;
}

void DirectionalLight::ChangeDirection(Vector3 offset)
{
	direction += glm::vec3(offset.x, offset.y, offset.z);
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void DirectionalLight::SetDirection(Vector3 direction)
{
	this->direction = direction.ToGlm();
}

glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

DirectionalLight::~DirectionalLight()
{
}
