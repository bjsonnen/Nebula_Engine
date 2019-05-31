#pragma once
#include "Light.h"

namespace NE
{
	class DirectionalLight :
		public Light
	{
	public:
		//! Create a directional light with standard parameters
		//! 
		DirectionalLight();
		//! Create a directional light with specific parameters
		//! @param shadowWidth Insert the width of the shadow texture
		//! @param shadowHeight Insert the height of the shadow texture
		//! @param red Insert the red parameter of RGB
		//! @param grren Insert the grren parameter of RGB
		//! @param blue Insert the blue parameter of RGB
		//! @param aIntensity Insert the intensity for ambient lighting
		//! @param dIntensity Insert the intensity for diffuse lighting
		//! @param xDir Insert the x direction
		//! @param yDir Insert the y direction
		//! @param zDir Insert the z direction
		DirectionalLight(unsigned int shadowWidth, unsigned int shadowHeight,
			float red, float green, float blue,
			float aIntensity, float dIntensity,
			float xDir, float yDir, float zDir);

		//! Use the current light
		//! @param ambientIntensityLocation Insert the ambientIntensity location in the shader
		//! @param ambientColorLocation Insert the ambientColor location in the shader
		//! @param diffuseIntensityLocation Insert the diffuseIntensity location in the shader
		//! @param directionLocation Insert the direction location in the shader
		void UseLight(float ambientIntensityLocation, float ambientColorLocation,
			float diffuseIntensityLocation, float directionLocation);

		//! Change the direction of the light
		//! @param Insert the offset of the direction as glm::vec3
		void ChangeDirection(glm::vec3 offset);
		//! Change the direction of the light
		//! @param Insert the offset of the direction as Vector3
		void ChangeDirection(Vector3 offset);

		//! Set the direction of the light
		//! @param Insert the direction as glm::vec3
		void SetDirection(glm::vec3 direction);
		//! Set the direction of the light
		//! @param Insert the direction as Vector3
		void SetDirection(Vector3 direction);

		//! Get the current direction
		//! @return Returns the current direction as glm::vec3
		glm::vec3 GetDirection()
		{
			return direction;
		};

		//! Calculate current Light Transform
		//! @return Returns the light transform as glm::mat4 (4x4 matrix)
		glm::mat4 CalculateLightTransform();

		~DirectionalLight();

	private:
		glm::vec3 direction;
	};


}
