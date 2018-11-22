#pragma once

#include <GL/glew.h>

class Hdr
{
public:
	// Create Textures
	Hdr();

	void StartParsing();
	void EndParsing();

	void RenderScene(void* x);

	~Hdr();

private:
	unsigned int hdrFBO;
	unsigned int colorBuffer;
};

