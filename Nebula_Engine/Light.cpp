#include "Light.h"

NE::Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
	// You have to create a shadow map, but do not init it!
	shadowMap = new ShadowMap();
}

NE::Light::Light(unsigned int shadowWidth, unsigned int shadowHeight, float red, float green, float blue, float aIntensity, float dIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;

	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
}

void NE::Light::SetColor(glm::vec3 color)
{
	this->color = color;
}

void NE::Light::SetColor(Vector3 color)
{
	this->color = color.ToGlm();
}

NE::Light::~Light()
{
}
