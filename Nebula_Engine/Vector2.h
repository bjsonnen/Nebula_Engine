#pragma once

#include <cmath>
#include <string>
#include <sstream>

#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\matrix_decompose.hpp>

namespace NE
{
	//! Main nebula engine vector2 class
//! Should be used for gameplay stuff
	class Vector2
	{
	public:
		float x;
		float y;

		//! Standard initialization for the vector2
		//! Sets all variables to 0
		Vector2()
		{
			x = 0;
			y = 0;
		}
		//! Initializes the vector with three diffrent values for the variables
		//! @param x X value as float
		//! @param y Y value as float
		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
		//! Initializes the vector with one value for all variables
		//! @param xy float input
		Vector2(float xy)
		{
			this->x = xy;
			this->y = xy;
		}
		//! Initializes the vector with a glm::vec2
		//! @param v glm::vec2 (2D Vector)
		Vector2(glm::vec2 v)
		{
			this->x = v.x;
			this->y = v.y;
		}

		//! Set the vector2 to zero (0.0)
		void Zero()
		{
			x = 0.0f;
			y = 0.0f;
		}

		//! Set the vector2 to another vector2
		//! @param x new NE::Vector2
		Vector2& operator =(Vector2 x)
		{
			this->x = x.x;
			this->y = x.y;
			return Vector2(this->x, this->y);
		}
		//! Adds one vector2 to another
		//! @param x New Vector2
		Vector2& operator +(Vector2 x)
		{
			this->x += x.x;
			this->y += x.y;
			return Vector2(this->x, this->y);
		}
		//! Subtracts one vector2 from another
		//! @param x New Vector2
		Vector2& operator -(Vector2 x)
		{
			this->x -= x.x;
			this->y -= x.y;
			return Vector2(this->x, this->y);
		}
		//! Set the vector3 to another vector2
		//! @param x New Vector2
		Vector2& operator =(glm::vec3 v)
		{
			this->x = v.x;
			this->y = v.y;
			return Vector2(this->x, this->y);
		}

		//! Divide the vector2 through a number
		Vector2& operator /(float s)
		{
			this->x /= s;
			this->y /= s;
			return Vector2(this->x, this->y);
		}

		//! Set a vector to two specific variables
		//! @param x Set the x value of the vector
		//! @param y Set the y value of the vector
		Vector2& SetVector2(float x, float y)
		{
			this->x = x;
			this->y = y;
			return Vector2(this->x, this->y);
		}

		//! Set a vector to one specific variables
		//! @param xy Set all variables to value
		Vector2& SetVector2(float xy)
		{
			this->x = xy;
			this->y = xy;
			return Vector2(this->x, this->y);
		}

		//! Calculates the dot product of two vectors
		//! @param v Insert other vector v here as Vector2
		//! @return Returns the dot product as float
		float Dot(Vector2 v)
		{
			return this->x * v.x + this->y * v.y;
		}

		//! Returns the magnitude of the vector
		//! @return Returns the magnitude as float
		float Magnitude()
		{
			return sqrt(this->x * this->x + this->y * this->y);
		}

		//! Normalizes the vector
		Vector2& Normalize()
		{
			float mag = Magnitude();
			this->x /= mag;
			this->y /= mag;
			return Vector2(this->x, this->y);
		}

		//! Converts vector2 to glm::vec2
		//! @return Returns a glm::vec2
		glm::vec2 ToGlm()
		{
			return glm::vec2(this->x, this->y);
		}

		//! Returns a Vector3 as std::string
		//! @return Returns the Vector2 as std::string
		std::string ToString()
		{
			std::stringstream tmp;
			tmp << "(" << this->x << " / " << this->y << ")";
			return tmp.str();
		}
	};
}