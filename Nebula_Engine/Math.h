#pragma once

#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace NE
{
	//! Main class for special math operations
	class Mathf
	{
	public:
		// Lerp a 3D Position slowly from one point another
		static glm::vec3& Lerp(glm::vec3& start, glm::vec3& target, float time)
		{
			float x = start.x + time * (target.x - start.x);
			float y = start.y + time * (target.y - start.y);
			float z = start.z + time * (target.z - start.z);

			return glm::vec3(x, y, z);
		}
		// Lerp a 2D Position slowly from one point another
		static glm::vec2& Lerp(glm::vec3& start, glm::vec2& target, float time)
		{
			float x = start.x + time * (target.x - start.x);
			float y = start.y + time * (target.y - start.y);

			return glm::vec2(x, y);
		}
		// Convert degrees to radians
		static float ToRadians(float degrees)
		{
			return (degrees * (3.14159265f / 180.0f));
		}
		// Convert radians to degrees
		static float ToDegrees(float radians)
		{
			return (radians / (3.14159265f / 180.0f));
		}
	};
}