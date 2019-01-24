#pragma once

#include <stdio.h>
#include <GL\glew.h>

#include "Util.h"

//! Base class for all shadow map relevant classes
class ShadowMap
{
public:
	//! Create ShadowMap with standard parameters
	ShadowMap();

	//! Initialize the shadow map
	//! @param width Insert texture width as unsigned int
	//! @param height Insert texture height as unsigned int
	virtual NE_ERROR Init(unsigned int width, unsigned int height);

	//! Write texture to the shader
	//! 
	virtual void Write();

	//! Read the texture from the shader
	//! @param TextureUnit Insert texture unit from shader as unsigned int
	virtual void Read(unsigned int TextureUnit);

	//! Retruns the shadow map width
	//! @return Returns the shaodw map width as unsigned int
	unsigned int GetShadowWidth() { return shadowWidth; }
	//! Retruns the shadow map height
	//! @return Returns the shaodw map height as unsigned int
	unsigned int GetShadowHeight() { return shadowHeight; }

	~ShadowMap();
protected:
	unsigned int FBO, shadowMap;
	unsigned int shadowWidth, shadowHeight;
};