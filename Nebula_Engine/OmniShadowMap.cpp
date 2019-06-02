#include "OmniShadowMap.h"

NE::OmniShadowMap::OmniShadowMap() : ShadowMap() {}

NE_ERROR NE::OmniShadowMap::Init(unsigned int width, unsigned int height)
{
	shadowWidth = width; shadowHeight = height;

	glGenFramebuffers(1, &FBO);

	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);

	for (size_t i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	}

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	unsigned int Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "OmniShadowMap: " << Status << std::endl;
		return NE_RENDERER;
	}

	return NE_OK;
}

void NE::OmniShadowMap::Write()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
}

void NE::OmniShadowMap::Read(unsigned int texUnit)
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMap);
}

NE::OmniShadowMap::~OmniShadowMap()
{
}
