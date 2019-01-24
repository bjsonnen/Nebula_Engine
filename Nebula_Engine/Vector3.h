#pragma once

#include <cmath>
#include <string>
#include <sstream>

#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\matrix_decompose.hpp>

//! Main nebula engine vector3 class
//! Should be used for gameplay stuff
struct Vector3
{
	float x;
	float y;
	float z;

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

	//! Returns the magnitude of the vector
	//! @return Returns the magnitude of the vector as float
	float Magnitude()
	{
		return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	}
	//! Returns the length of the vector
	//! @return Returns the length as float
	float Length()
	{
		std::sqrt(this->x + this->y + this->z);
	}

	//! Normalizes a vector, so that x, y, z together are 1
	//! 
	void Normalize()
	{
		this->x = std::sqrt(this->x * this->x);
		this->y = std::sqrt(this->y * this->y);
		this->z = std::sqrt(this->z * this->z);
	}

	//! Set the vector3 to another vector3
	//! @param x New Vector3
	//! @return Returns the new Vector3 as Vector3
	Vector3 operator =(Vector3 x)
	{
		this->x = x.x;
		this->y = x.y;
		this->z = x.z;
	}
	//! Adds a vector3 to another vector3
	//! @param x New Vector3
	//! @return Returns the new Vector3 as Vector3
	Vector3 operator +(Vector3 x)
	{
		this->x += x.x;
		this->y += x.y;
		this->z += x.z;
	}
	//! Subtract vector3 x from vector3
	//! @param x Vector3
	//! @see Vector3()
	//! @return Returns the new Vector as Vector3
	Vector3 operator -(Vector3 x)
	{
		this->x -= x.x;
		this->y -= x.y;
		this->z -= x.z;
	}

	//! Set x, y, z to v
	//! @param v glm::vec3 to Vector3
	//! @see Vector3()
	//! @return Returns the new Vector as Vector3
	Vector3 operator =(glm::vec3 v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	//! Returns a Vector3 as const char array
	//! @return Returns the Vector3 as char pointer (char*)
	const char* ToString()
	{
		std::ostringstream oss;
		oss << "(" << x << " / " << this->y << " / " << this->z << ")";
		const char* ca = oss.str().c_str();
		return ca;
	}

public:
	//! Calculates the dot product between two vectors
	//! @param a First Vector3
	//! @param b Second Vector3
	//! @return Returns the dot product as float
	static float Dot(Vector3 a, Vector3 b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}
};