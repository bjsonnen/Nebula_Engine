#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Math
{
public:
	Math();

	// Lerp a 3D Vector to another
	static glm::vec3 Lerp(glm::vec3 start, glm::vec3 target, float time);
	// Lerp a 2D Vector to another
	static glm::vec2 Lerp(glm::vec2 start, glm::vec2 target, float time);

	~Math();
};

