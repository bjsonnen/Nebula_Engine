#pragma once

#include <cmath>
#include <string>
#include <sstream>

#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\matrix_decompose.hpp>

//! Main nebula engine vector2 class
//! Should be used for gameplay stuff
struct Vector2
{
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
	//! Returns the magnitude of the vector
	//! @return Returns the magnitude of the vector as float
	float Magnitude()
	{
		return std::sqrt((this->x * this->x) + (this->y * this->y));
	}
	//! Returns the length of the vector
	//! @return Returns the length as float
	float Length()
	{
		std::sqrt(this->x + this->y);
	}
	//! Normalizes a vector, so that x, y together are 1
	//! 
	void Normalize()
	{
		std::sqrt(this->x * this->x) + std::sqrt(this->y);
	}
	//! Set the vector2 to zero
	//!
	void Zero()
	{
		x = 0;
		y = 0;
	}
	//! Set the vector2 to another vector2
	//! @param x New Vector2
	//! @return Returns the new Vector2 as Vector2
	Vector2 operator =(Vector2 x)
	{
		this->x = x.x;
		this->y = x.y;
	}
	//! Adds one vector2 to another
	//! @param x New Vector2
	//! @return Returns the new Vector2 as Vector2
	Vector2 operator +(Vector2 x)
	{
		this->x += x.x;
		this->y += x.y;
	}
	//! Subtracts one vector2 from another
	//! @param x New Vector2
	//! @return Returns the new Vector2 as Vector2
	Vector2 operator -(Vector2 x)
	{
		this->x -= x.x;
		this->y -= x.y;
	}
	//! Subtracts one vector2 from another
	//! @param x New Vector2
	//! @return Returns the new Vector2 as Vector2
	Vector2 operator -=(Vector2 x)
	{
		this->x -= x.y;
		this->y -= x.y;
	}
	//! Adds one vector2 to another
	//! @param x New Vector2
	//! @return Returns the new Vector2 as Vector2
	Vector2 operator +=(Vector2 x)
	{
		this->x += x.y;
		this->y += x.y;
	}
	//! Set the vector3 to another vector2
	//! @param x New Vector2
	//! @return Returns the new Vector2 as Vector2
	Vector2 operator =(glm::vec3 v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	//! Returns a Vector3 as const char array
	//! @return Returns the Vector2 as char pointer (char*)
	const char* ToString()
	{
		//std::string test = "(" + std::to_string(1);
		//return test.c_str();
		return "awdwa";
	}
};