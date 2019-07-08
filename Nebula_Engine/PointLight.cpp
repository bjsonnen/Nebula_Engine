#include "PointLight.h"



NE::PointLight::PointLight() : Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
	shadowMap = new NE::OmniShadowMap();
	// -> Cant access something
	//shadowMap->Init(1920, 1080);
}

NE::PointLight::PointLight(unsigned int shadowWidth, unsigned int shadowHeight,
						float near, float far, 
						float red, float green, float blue,
						float aIntensity, float dIntensity, 
						float xPos, float yPos, float zPos, 
						float con, float lin, float exp) : Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
{
	position = glm::vec3(xPos, yPos, zPos);
	constant = con;
	linear = lin;
	exponent = exp;

	farPlane = far;

	float aspect = (float)shadowWidth / (float)shadowHeight;
	lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

	shadowMap = new NE::OmniShadowMap();
	// -> Cant access something
	NE_DEBUG_LOG(shadowMap->Init(shadowWidth, shadowHeight));
}

void NE::PointLight::UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColorLocation,
	unsigned int diffuseIntensityLocation, unsigned int positionLocation,
	unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}

std::vector<glm::mat4> NE::PointLight::CalculateLightTransform()
{
	std::vector<glm::mat4> lightMatrices;

	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));

	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));

	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	lightMatrices.push_back(lightProj * glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	return lightMatrices;
}

float NE::PointLight::GetFarPlane()
{
	return farPlane;
}
void NE::PointLight::SetColor(glm::vec3 color)
{
	Light::SetColor(color);
}
void NE::PointLight::SetColor(Vector3 color)
{
	Light::SetColor(color.ToGlm());
}
void NE::PointLight::SetPosition(glm::vec3 pos)
{
	position = pos;
}
void NE::PointLight::SetPosition(Vector3 pos)
{
	position = pos.ToGlm();
}
glm::vec3 NE::PointLight::GetPosition()
{
	return position;
}

NE::Vector3 NE::PointLight::GetPositionVector3()
{
	return Vector3(position.x, position.y, position.z);
}

NE::PointLight::~PointLight()
{
}
