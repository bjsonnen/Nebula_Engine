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
	//! Main nebula engine vector3 class
	//! Should be used for gameplay stuff
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

		// -- Constructor --

		//! Standard initialization for the vector3
		//! Sets all variables to 0
		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		//! Initializes the vector with three diffrent values for the variables
		//! @param x X value as float
		//! @param y Y value as float
		//! @param z Z value as float
		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		//! Initializes the vector with one value for all variables
		//! @param xyz float input
		Vector3(float xyz)
		{
			x = xyz;
			y = xyz;
			z = xyz;
		}

		//! Initializes the vector with a glm::vec3
		//! @param v glm::vec3 (3D Vector)
		Vector3(glm::vec3 v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		// -- operators --

		//! Adds a vector3 to another vector3
		//! @param x New Vector3
		//! @return Returns the new Vector3 as Vector3
		Vector3& operator +(Vector3& x)
		{
			this->x += x.x;
			this->y += x.y;
			this->z += x.z;
			return Vector3(this->x, this->y, this->z);
		}

		//! Subtract vector3 x from vector3
		//! @param x Insert subtraction Vector as const Vector3
		//! @return Returns the new Vector as Vector3
		Vector3& operator -(Vector3& x)
		{
			this->x -= x.x;
			this->y -= x.y;
			this->z -= x.z;
			return Vector3(this->x, this->y, this->z);
		}

		//! Subtract Vector3 x from const Vector3 y
		//! @param x Insert subtraction Vector as const Vector3
		//! @return Returns the new Vector as const Vector3
		const Vector3& operator -(const Vector3& x) const
		{
			return Vector3(this->x - x.x, this->y - x.y, this->z - x.z);
		}

		//! Set x, y, z to v
		//! @param v glm::vec3 to Vector3
		//! @return Returns the new Vector as Vector3
		Vector3& operator =(glm::vec3& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return Vector3(this->x, this->y, this->z);
		}

		//! Set the vector3 to another vector3
		//! @param x New Vector3
		//! @return Returns the new Vector3 as Vector3
		Vector3& operator =(Vector3& x)
		{
			this->x = x.x;
			this->y = x.y;
			this->z = x.z;
			return Vector3(this->x, this->y, this->z);
		}

		//! Divides the vector through a scalar
		//! @param x The scalar for the division
		Vector3& operator /(float x)
		{
			return Vector3(this->x / x,
				this->y / x,
				this->z / x);
		}

		//! Multiplies the vector 3 with a value
		//! @param x Insert multiply value as float
		//! @return Returns the new Vector as Vector3&
		Vector3& operator *(float x)
		{
			return Vector3(this->x * x,
				this->y * x,
				this->z * z);
		}

		//! Multiplies the vector 3 with a value
		//! @param x Insert multiply value as float
		//! @return Returns the new Vector as const Vector3&
		const Vector3& operator *(float x) const
		{
			return Vector3(this->x * x,
				this->y * x,
				this->z * z);
		}

		// -- methods --

		//! Set a vector to three specific variables
		//! @param x Set the x value of the vector
		//! @param y Set the y value of the vector
		//! @param z Set the z value of the vector
		Vector3& SetVector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			return Vector3(this->x, this->y, this->z);
		}

		//! Set a vector to two specific variables
		//! @param x Set the x value of the vector
		//! @param y Set the y value of the vector
		Vector3& SetVector3(float x, float y)
		{
			this->x = x;
			this->y = y;
			this->z = 0.0f;
			return Vector3(this->x, this->y, this->z);
		}

		//! Set a vector to one specific variables
		//! @param xyz Set all variables to value
		Vector3& SetVector3(float xyz)
		{
			this->x = xyz;
			this->y = xyz;
			this->z = xyz;
			return Vector3(this->x, this->y, this->z);
		}

		//! Set all vector variables to zero (0.0)
		Vector3& Zero()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			return Vector3(this->x, this->y, this->z);
		}


		//! Calculates the dot product of two vectors
		//! @param v Insert other vector v here as Vector3
		//! @return Returns the dot product as float
		static float Dot(const Vector3& a, const Vector3& b)
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		//! Projects one vector on another
		//! @param a Insert vector to project on the other as Vector3
		//! @param b Insert main vector for projection as const Vector3
		//! @return Returns a new vector3 as Vector3&
		static Vector3& Project(Vector3& a, Vector3& b)
		{
			return (b * (Dot(a, b) / Dot(b, b)));
		}

		//! Projects one vector on another
		//! @param a Insert vector to project on the other as const Vector3
		//! @param b Insert main vector for projection as const Vector3
		//! @return Returns a new vector3 as const Vector3&
		static const Vector3& Project(const Vector3& a, const Vector3& b)
		{
			return (b * (Dot(a, b) / Dot(b, b)));
		}

		//! Rejects one vector from another
		//! @param a Insert vector to reject on the other as Vector3
		//! @param b Insert main vector as Vector3
		//! @return Returns a new vector as Vector3&
		static Vector3& Reject(Vector3& a, Vector3 b)
		{
			return (a - b * (Dot(a, b) / (Dot(b, b))));
		}

		//! Rejects one vector from another
		//! @param a Insert vector to reject on the other as const Vector3
		//! @param b Insert main vector as const Vector3
		//! @return Returns a new vector as const Vector3&
		static const Vector3& Reject(const Vector3& a, const Vector3 b)
		{
			return (a - b * (Dot(a, b) / (Dot(b, b))));
		}

		//! Calculates the cross product of two vectors
		//! @param a Insert the first vector here as Vector3
		//! @param b Insert the second vector here as Vector3
		//! @return Returns the new Cross-Vector as Vector3
		static Vector3& Cross(Vector3& a, Vector3& b)
		{
			return Vector3(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
		}

		//! Calculates the cross product of two vectors
		//! @param a Insert the first vector here as const Vector3
		//! @param b Insert the second vector here as const Vector3
		//! @return Returns the new Cross-Vector as const Vector3
		static const Vector3& Cross(const Vector3& a, const Vector3& b)
		{
			return Vector3(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
		}

		//! Returns the magnitude of the vector
		//! @return Returns the magnitude as float
		float Magnitude()
		{
			return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		}

		//! Normalizes the vector
		//! @return Returns the normalized vector as Vector3&
		Vector3& Normalize()
		{
			float mag = Magnitude();
			this->x /= mag;
			this->y /= mag;
			this->z /= mag;
			return Vector3(this->x, this->y, this->z);
		}

		//! Converts vector3 to glm::vec3
		//! @return Returns a glm::vec3
		glm::vec3 ToGlm()
		{
			return glm::vec3(this->x, this->y, this->z);
		}

		//! Returns a Vector3 as std::string
		//! @return Returns the Vector3 as std::string
		std::string ToString()
		{
			std::stringstream tmp;
			tmp << "(" << this->x << " / " << this->y << " / " << this->z << ")";
			return tmp.str();
		}
	};
}