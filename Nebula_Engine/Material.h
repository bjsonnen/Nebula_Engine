#pragma once

#include <GL\glew.h>
#include "Shader.h"

//! Main class to create a new material
class Material
{
public:
	//! Create a material with standard paramerters
	//!
	Material();
	//! Create a material with specific paramaters
	//! @param sIntensity Insert specular intensity as float
	//! @param shine Insert shine as float
	Material(float sIntensity, float shine);

	//! Use material
	//! @param specularIntensityLocation Insert specularIntensity location in the shader
	//! @param shininessLocation Insert shininess location in the shader
	void UseMaterial(unsigned int specularIntensityLocation, unsigned int shininessLocation);
	//! Use material
	//! @param shader Insert shader pointer (Shader*)
	void UseMaterial(Shader* shader);

	~Material();

private: 
	float specularIntensity;
	float shininess;
};

