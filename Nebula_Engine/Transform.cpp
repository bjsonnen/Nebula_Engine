#include "Transform.h"

void Transform::Init()
{
	pos = glm::vec3();
	rota = glm::vec3();
	scale = glm::vec3();
}

void Transform::Update()
{
}

void Transform::SetPosition(glm::vec3 position)
{
	pos = position;
}

void Transform::SetPosition(float x, float y, float z)
{
	rota = glm::vec3(x, y, z);
}

void Transform::SetRotation(glm::vec3 rotation)
{
	rota = rotation;
}

void Transform::SetRotation(float x, float y, float z)
{
	rota = glm::vec3(x, y, z);
}

void Transform::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}

void Transform::SetScale(float x, float y, float z)
{
	scale = glm::vec3(x, y, z);
}

void Transform::Rotate(glm::vec3 rotation)
{
	rota += rotation;
}

void Transform::Rotate(float x, float y, float z)
{
	rota += glm::vec3(x, y, z);
}

void Transform::LookAt(glm::vec3 pos)
{
	rota = pos;
}

void Transform::LookAt(glm::vec2 pos)
{
	rota = glm::vec3(pos.x, pos.y, 0.0f);
}

void Transform::LookAt(float x, float y, float z)
{
	rota = glm::vec3(x, y, z);
}

float Transform::GetDegrees()
{
	return degrees;
}

void Transform::SetDegrees(float degrees)
{
	this->degrees = degrees;
}

glm::vec3 Transform::GetPosition()
{
	return pos;
}

glm::vec3 Transform::GetRotation()
{
	return rota;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}
