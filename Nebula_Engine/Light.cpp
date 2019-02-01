#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(unsigned int shadowWidth, unsigned int shadowHeight, float red, float green, float blue, float aIntensity, float dIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;

	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
}

void Light::SetColor(glm::vec3 color)
{
	this->color = color;
}

void Light::SetColor(Vector3 color)
{
	this->color = color.ToGlm();
}

Light::~Light()
{
}
