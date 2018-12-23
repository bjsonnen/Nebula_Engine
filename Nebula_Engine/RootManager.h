#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include "GameObject.h"

class RootManager
{
public:
	RootManager();
	~RootManager();

public:
	void StartUo();
	void ShutDown();
	static void RenderObjects(GameObject* input, int count);
};

