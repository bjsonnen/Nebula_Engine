#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Window.h"

class PostProcessing
{
public:
	PostProcessing();
	//PostProcessing(Shader* shader, Window* window);

	void Awake();

	void StartParsing();
	void EndParsing();

	~PostProcessing();

private:
	Mesh* mainMesh;
	Shader* mainShader;

	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	unsigned int rbo;
};