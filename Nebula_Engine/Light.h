#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "ShadowMap.h"

namespace NE
{
	//! Main class for light in general
	class Light
	{
	public:
		//! Create a light with standard paramerters
		//!
		Light();
		//! Create alight with specific parameters
		//! @param shadowWidth Shadow texture width as unsigned int
		//! @param shadowHeight Shadow texture height as unsigned int
		//! @param red Insert red value of RGB as float
		//! @param green Insert green value of RGB as float
		//! @param blue Insert blue value of RGB as float
		//! @param aIntensity Insert ambient Intensity as float
		//! @param dIntensity Insert diffuse Intensity as float
		Light(unsigned int shadowWidth, unsigned int shadowHeight,
			float red, float green, float blue,
			float aIntensity, float dIntensity);

		//! Change the color of the light
		//! @param color Insert new color for the light as glm::vec3
		void SetColor(glm::vec3 color);
		//! Change the color of the light
		//! @param color Insert new color for the light as Vector3
		void SetColor(Vector3 color);

		//! Get shadow map
		//! @return Returns a ShadowMap pointer (ShadowMap*)
		//! @see ShadowMap
		//ShadowMap* getShadowMap() { return shadowMap; }
		ShadowMap* GetShadowMap() { return shadowMap; }

		~Light();

	protected:
		glm::vec3 color;
		float ambientIntensity;
		float diffuseIntensity;

		glm::mat4 lightProj;

		ShadowMap* shadowMap;
	};


}
