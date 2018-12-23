#pragma once

#include "ShadowMap.h"
#include "Util.h"

class OmniShadowMap :
	public ShadowMap
{
public:
	OmniShadowMap();

	NE_ERROR Init(unsigned int width, unsigned int height);

	void Write();

	void Read(unsigned int TextureUnit);

	~OmniShadowMap();
};

