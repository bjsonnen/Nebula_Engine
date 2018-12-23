#include "RootManager.h"



RootManager::RootManager()
{
}


RootManager::~RootManager()
{
}

void RootManager::RenderObjects(GameObject * input, int count)
{
	glm::mat4 model;

	for (int i = 0; i < count; i++)
	{
		if (!input[i].IsActive())
			return;
	}

}
