#include "Material.h"



NE::Material::Material()
{
	specularIntensity = 0.0f;
	shininess = 0.0f;
}

NE::Material::Material(float sIntensity, float shine)
{
	specularIntensity = sIntensity;
	shininess = shine;
}

void NE::Material::UseMaterial(unsigned int specularIntensityLocation, unsigned int shininessLocation)
{
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform1f(shininessLocation, shininess);
}

void NE::Material::UseMaterial(NE::Shader * shader)
{
	shader->SetFloat("material.specularIntensity", specularIntensity);
	shader->SetFloat("material.shininess", shininess);
}

NE::Material::~Material()
{
}
