#pragma once
#include "PointLight.h"

namespace NE
{
	//! Main class to create a spot light
	class SpotLight :
		public PointLight
	{
	public:
		//! Create spotlight with standard parameters
		SpotLight();
		//! Create a Spot Light with specific parameters
		//! @param shadowWidth Shadow width as unsigned int
		//! @param shadowHeight Shadow height as unsigned int
		//! @param near Near plane as float
		//! @param far Far plane as float
		//! @param red Red value in RGB as float
		//! @param green Green value in RGB as float
		//! @param blue Blue value in RGB as float
		//! @param aIntensity Insert ambient intensity as float
		//! @param dIntensity Insert diffuse intensity as float
		//! @param xPos Insert position X value as float
		//! @param yPos Insert position Y value as float
		//! @param zPos Insert position Z value as float
		SpotLight(unsigned int shadowWidth, unsigned int shadowHeight,
			float near, float far,
			float red, float green, float blue,
			float aIntensity, float dIntensity,
			float xPos, float yPos, float zPos,
			float xDir, float yDir, float zDir,
			float con, float lin, float exp,
			float edg);

		//! Use light
		//! @param ambientIntensityLocation Insert ambientIntensity location in shader
		//! @param ambientColourLocation Insert ambientColor location in shader
		//! @param diffuseIntensityLocation Insert diffuseIntensity location in shader
		//! @param positionLocation Insert position location in shader
		//! @param constantLocation Insert constant location in shader
		//! @param linearLocation Insert linear location in shader
		//! @param exponentLocation Insert exponent location in shader
		void UseLight(unsigned int ambientIntensityLocation, unsigned int ambientColourLocation,
			unsigned int diffuseIntensityLocation, unsigned int positionLocation, unsigned int directionLocation,
			unsigned int constantLocation, unsigned int linearLocation, unsigned int exponentLocation,
			unsigned int edgeLocation);

		//! Change position and direction
		//! @param pos Set position as glm::vec3
		//! @param dir Set direction as glm::vec3
		void SetFlash(glm::vec3 pos, glm::vec3 dir);
		//! Change position and direction
		//! @param pos Set position as Vector3
		//! @param dir Set direction as Vector3
		void SetFlash(Vector3 pos, Vector3 dir);

		//! Change position
		//! @param pos Set position as glm::vec3
		void SetPosition(glm::vec3 pos);
		//! Change position
		//! @param pos Set position as Vector3
		void SetPosition(Vector3 pos);
		//! Change direction
		//! @param pos Set direction as glm::vec3
		void SetDirection(glm::vec3 dir);
		//! Change direction
		//! @param pos Set direction as Vector3
		void SetDirection(Vector3 dir);

		//! Change color of the spot light
		//! @param color Set new color of the light as glm::vec3
		void SetColor(glm::vec3 color);
		//! Change color of the spot light
		//! @param color Set new color of the light as Vector3
		void SetColor(Vector3 color);

		//! Turn light on or off
		//!
		void Toggle();

		~SpotLight();

	private:
		glm::vec3 direction;

		float edge, procEdge;

		bool isOn;
	};


}
