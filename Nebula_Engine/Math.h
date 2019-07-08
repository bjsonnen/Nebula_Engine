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
		//! Lerp a 3D Position slowly from one point another
		//! @param start The start vector as glm::vec3&
		//! @param start The end vector as glm::vec3&
		//! @param time Time for lerp as flat
		//! @return Returns the new vector as glm::vec3&
		static glm::vec3& Lerp(glm::vec3& start, glm::vec3& target, float time)
		{
			float x = start.x + time * (target.x - start.x);
			float y = start.y + time * (target.y - start.y);
			float z = start.z + time * (target.z - start.z);

			return glm::vec3(x, y, z);
		}

		//! Lerp a 3D Position slowly from one point another
		//! @param start The start vector as NE::Vector3&
		//! @param start The end vector as NE::Vector3&
		//! @param time Time for lerp as flat
		//! @return Returns the new vector as NE::Vector3&
		static NE::Vector3& Lerp(NE::Vector3& start, NE::Vector3& target, float time)
		{
			float x = start.x + time * (target.x - start.x);
			float y = start.y + time * (target.y - start.y);
			float z = start.z + time * (target.z - start.z);

			return NE::Vector3(x, y, z);
		}

		//! Lerp a 2D Position slowly from one point another
		//! @param start The start vector as glm::vec2&
		//! @param start The end vector as glm::vec2&
		//! @param time Time for lerp as flat
		//! @return Returns the new vector as glm::vec2&
		static glm::vec2& Lerp(glm::vec3& start, glm::vec2& target, float time)
		{
			float x = start.x + time * (target.x - start.x);
			float y = start.y + time * (target.y - start.y);

			return glm::vec2(x, y);
		}

		//! Lerp a 2D Position slowly from one point another
		//! @param start The start vector as NE::Vector2&
		//! @param start The end vector as NE::Vector2&
		//! @param time Time for lerp as flat
		//! @return Returns the new vector as NE::Vector2&
		static NE::Vector2& Lerp(NE::Vector2& start, NE::Vector2& target, float time)
		{
			float x = start.x + time * (target.x - start.x);
			float y = start.y + time * (target.y - start.y);

			return NE::Vector2(x, y);
		}

		//! Convert degrees to radians
		//! @param degrees Degrees to convert to radians
		//! @return Returns the new radians value
		static float ToRadians(float degrees)
		{
			return (degrees * (3.14159265f / 180.0f));
		}

		//! Convert radians to degrees
		//! @param degrees Radians to convert to degrees
		//! @return Returns the new degree value
		static float ToDegrees(float radians)
		{
			return (radians / (3.14159265f / 180.0f));
		}
	};
}