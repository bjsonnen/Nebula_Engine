#include "DirectionalLight.h"

NE::DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

NE::DirectionalLight::DirectionalLight(unsigned int shadowWidth, unsigned int shadowHeight,
									float red, float green, float blue,
									float aIntensity, float dIntensity,
									float xDir, float yDir, float zDir) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);

	lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

void NE::DirectionalLight::UseLight(float ambientIntensityLocation, float ambientColorLocation,
	float diffuseIntensityLocation, float directionLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

void NE::DirectionalLight::ChangeDirection(glm::vec3 offset)
{
	direction += offset;
}

void NE::DirectionalLight::ChangeDirection(Vector3 offset)
{
	direction += glm::vec3(offset.x, offset.y, offset.z);
}

void NE::DirectionalLight::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void NE::DirectionalLight::SetDirection(Vector3 direction)
{
	this->direction = direction.ToGlm();
}

glm::mat4 NE::DirectionalLight::CalculateLightTransform()
{
	return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

NE::DirectionalLight::~DirectionalLight()
{
}
