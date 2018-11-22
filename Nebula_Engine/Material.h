#pragma once

#include <GL\glew.h>
#include "Shader.h"

class Material
{
public:
	Material();
	Material(float sIntensity, float shine);

	// Use material
	void UseMaterial(unsigned int specularIntensityLocation, unsigned int shininessLocation);
	// Use material
	void UseMaterial(Shader* shader);

	~Material();

private: 
	float specularIntensity;
	float shininess;
};

