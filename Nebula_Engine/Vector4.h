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
	class Vector4
	{
	public:
		float x, y, z, w;

		//! Standard initialization for the vector2
		//! Sets all variables to 0
		Vector4()
		{
			Zero();
		}

		//! Initializes the vector with three diffrent values for the variables
		//! @param x X value as float
		//! @param y Y value as float
		//! @param z Z value as float
		//! @param w W value as float
		Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		//! Initializes the vector with one value for all variables
		//! @param xyzw float input
		Vector4(float xyzw)
		{
			this->x = xyzw;
			this->y = xyzw;
			this->z = xyzw;
			this->w = xyzw;
		}

		//! Initializes the vector with a glm::vec4
		//! @param v glm::vec4 (2D Vector)
		Vector4(glm::vec4 v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
		}

		//! Set the vector2 to zero (0.0)
		void Zero()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 0.0f;
		}

		//! Set the vector4 to another vector4
		//! @param x new NE::Vector4
		Vector4& operator =(Vector4& x)
		{
			this->x = x.x;
			this->y = x.y;
			this->z = x.z;
			this->w = x.w;
			return Vector4(this->x, this->y, this->z, this->w);
		}

		//! Adds one vector4 to another
		//! @param x new NE::Vector4
		Vector4& operator +(Vector4& x)
		{
			this->x += x.x;
			this->y += x.y;
			this->z += x.z;
			this->w += x.w;
			return Vector4(this->x, this->y, this->z, this->w);
		}

		//! Subtracts one vector4 from another
		//! @param x new NE::Vector4
		Vector4& operator -(Vector4& x)
		{
			this->x -= x.x;
			this->y -= x.y;
			this->z -= x.z;
			this->w -= x.w;
			return Vector4(this->x, this->y, this->z, this->w);
		}

		//! Divide the vector4 through a number
		//! @param s Value to divided through as float
		//! @return Returns the new vector as NE::Vector4
		Vector4& operator /(float s)
		{
			this->x /= s;
			this->y /= s;
			this->z /= s;
			this->w /= s;
			return Vector4(this->x, this->y, this->z, this->w);
		}

		//! Multiplies the vector4 by a number
		//! @param s Value to multiplied by as float
		//! @return Returns the new vector as NE::Vector4
		Vector4& operator *(float s)
		{
			this->x *= s;
			this->y *= s;
			this->z *= s;
			this->w *= s;
			return Vector4(this->x, this->y, this->z, this->w);
		}

		//! Set a vector to two specific variables
		//! @param x Set the x value of the vector
		//! @param y Set the y value of the vector
		//! @param z Set the z value of the vector
		//! @param w Set the w value of the vector
		Vector4& SetVector4(float x, float y)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
			return Vector4(this->x, this->y, this->z, this->w);
		}

		//! Set a vector to one specific variables
		//! @param xyzw Set all variables to value
		Vector4& SetVector2(float xyzw)
		{
			this->x = xyzw;
			this->y = xyzw;
			this->z = xyzw;
			this->w = xyzw;
			return Vector4(this->x, this->y, this->z, this->w);
		}

		//! Returns the magnitude of the vector
		//! @return Returns the magnitude as float
		float Magnitude()
		{
			return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
		}

		//! Normalizes the vector
		Vector4& Normalize()
		{
			float mag = Magnitude();
			this->x /= mag;
			this->y /= mag;
			this->z /= mag;
			this->w /= mag;
			return Vector4(this->x, this->y, this->z, this->w);
		}

		//! Converts vector4 to glm::vec4
		//! @return Returns a glm::vec4
		glm::vec4 ToGlm()
		{
			return glm::vec4(this->x, this->y, this->z, this->w);
		}

		//! Returns a Vector4 as std::string
		//! @return Returns the NE::Vector4 as std::string
		std::string ToString()
		{
			std::stringstream tmp;
			tmp << "(" << this->x << " / " << this->y << " / " << this->z << " / " << this->w << ")";
			return tmp.str();
		}
	};
}