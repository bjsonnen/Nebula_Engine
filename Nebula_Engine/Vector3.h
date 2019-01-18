#pragma once

#include <cmath>
#include <string>
#include <sstream>

#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\matrix_decompose.hpp>

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3(float xyz)
	{
		x = xyz;
		y = xyz;
		z = xyz;
	}

	Vector3(glm::vec3 v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	float Magnitude()
	{
		return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	}
	float Length()
	{
		std::sqrt(this->x + this->y + this->z);
	}

	void Normalize()
	{
		this->x = std::sqrt(this->x * this->x);
		this->y = std::sqrt(this->y * this->y);
		this->z = std::sqrt(this->z * this->z);
	}

	Vector3 operator =(Vector3 x)
	{
		this->x = x.x;
		this->y = x.y;
		this->z = x.z;
	}
	Vector3 operator +(Vector3 x)
	{
		this->x += x.x;
		this->y += x.y;
		this->z += x.z;
	}
	Vector3 operator -(Vector3 x)
	{
		this->x -= x.x;
		this->y -= x.y;
		this->z -= x.z;
	}

	Vector3 operator =(glm::vec3 v)
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	const char* ToString()
	{
		std::ostringstream oss;
		oss << "(" << x << " / " << this->y << " / " << this->z << ")";
		const char* ca = oss.str().c_str();
		return ca;
	}

public:
	static float Dot(Vector3 a, Vector3 b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}
};