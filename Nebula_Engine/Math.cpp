#include "Math.h"



Math::Math()
{
}

glm::vec3 Math::Lerp(glm::vec3 start, glm::vec3 target, float time)
{
	float x = start.x + time * (target.x - start.x);
	float y = start.y + time * (target.y - start.y);
	float z = start.z + time * (target.z - start.z);

	return glm::vec3(x, y, z);
}

glm::vec2 Math::Lerp(glm::vec2 start, glm::vec2 target, float time)
{
	float x = start.x + time * (target.x - start.x);
	float y = start.y + time * (target.y - start.y);
	
	return glm::vec2(x, y);
}


Math::~Math()
{
}
