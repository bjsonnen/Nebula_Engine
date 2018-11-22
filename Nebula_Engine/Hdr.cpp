#include "Hdr.h"



Hdr::Hdr()
{
}

void Hdr::RenderScene(void * x)
{
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	static_cast<void>(x);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Use Shader
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorBuffer);
}


Hdr::~Hdr()
{
}
