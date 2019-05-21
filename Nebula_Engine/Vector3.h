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

	//! Set a vector to three specific variables
	//! @param x Set the x value of the vector
	//! @param y Set the y value of the vector
	//! @param z Set the z value of the vector
	void SetVector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//! Set a vector to two specific variables
	//! @param x Set the x value of the vector
	//! @param y Set the y value of the vector
	void SetVector3(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	//! Set a vector to one specific variables
	//! @param xyz Set all variables to value
	void SetVector3(float xyz)
	{
		this->x = xyz;
		this->y = xyz;
		this->z = xyz;
	}

	//! Set all vector variables to zero (0.0)
	void Zero()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	//! Set the vector3 to another vector3
	//! @param x New Vector3
	//! @return Returns the new Vector3 as Vector3
	void operator =(Vector3 x)
	{
		this->x = x.x;
		this->y = x.y;
		this->z = x.z;
	}
	//! Adds a vector3 to another vector3
	//! @param x New Vector3
	//! @return Returns the new Vector3 as Vector3
	void operator +(Vector3 x)
	{
		this->x += x.x;
		this->y += x.y;
		this->z += x.z;
	}
	//! Subtract vector3 x from vector3
	//! @param x Vector3
	//! @see Vector3()
	//! @return Returns the new Vector as Vector3
	void operator -(Vector3 x)
	{
		this->x -= x.x;
		this->y -= x.y;
		this->z -= x.z;
	}

	//! Set x, y, z to v
	//! @param v glm::vec3 to Vector3
	//! @return Returns the new Vector as Vector3
	void operator =(glm::vec3 v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
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