#pragma once

#include <cmath>
#include <string>
#include <sstream>

#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\matrix_decompose.hpp>

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(float xy)
	{
		this->x = xy;
		this->y = xy;
	}

	Vector2(glm::vec2 v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	float Magnitude()
	{
		return std::sqrt((this->x * this->x) + (this->y * this->y));
	}
	float Length()
	{
		std::sqrt(this->x + this->y);
	}

	void Normalize()
	{
		std::sqrt(this->x * this->x) + std::sqrt(this->y);
	}

	void Zero()
	{
		x = 0;
		y = 0;
	}

	Vector2 operator =(Vector2 x)
	{
		this->x = x.x;
		this->y = x.y;
	}
	Vector2 operator +(Vector2 x)
	{
		this->x += x.x;
		this->y += x.y;
	}
	Vector2 operator -(Vector2 x)
	{
		this->x -= x.x;
		this->y -= x.y;
	}

	Vector2 operator -=(Vector2 x)
	{
		this->x -= x.y;
		this->y -= x.y;
	}
	Vector2 operator +=(Vector2 x)
	{
		this->x += x.y;
		this->y += x.y;
	}
	Vector2 operator *=(Vector2 x)
	{
		this->x *= x.y;
		this->y *= x.y;
	}
	Vector2 operator /=(Vector2 x)
	{
		this->x /= x.y;
		this->y /= x.y;
	}
	Vector2 operator =(glm::vec2 v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	// Returns the vector2 as an array of chars
	const char* ToString()
	{
		//std::string test = "(" + std::to_string(1);
		//return test.c_str();
		return "awdwa";
	}

public:
	static float Dot(Vector2 a, Vector2 b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

};