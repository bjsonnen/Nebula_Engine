#pragma once

#include "ShadowMap.h"
#include "Util.h"

namespace NE
{
	//! Main class to create a omnidirectional shadow map
	class OmniShadowMap :
		public ShadowMap
	{
	public:
		//! Create an OmniShadowMap with standard parameters
		//!
		OmniShadowMap();

		//! Initialize the Omni Shadow Map
		//! @param width Width of the omni shadow map as unsigned int
		//! @param width Height of the omni shadow map as unsigned int
		//! @return Returns a NE_ERROR
		//! @see NE_ERROR_CHECK
		NE_ERROR Init(unsigned int width, unsigned int height);

		//! Write the shadow map to the gpu
		//!
		void Write();

		//! Read the shaodw map from the gpu
		//! @param TextureUnit Insert texture location of the texture
		void Read(unsigned int TextureUnit);

		~OmniShadowMap();
	};
}

