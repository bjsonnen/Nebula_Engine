#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "ECManager.h"
#include "Util.h"

//! Main transforming class, Entity-Component-System sub-class
class Transform : public Component
{
public:
	// Automatically called 
	void Init() override;
	// Automatically called 
	void Update() override;

	// Set the position of the object
	// Position is automatically applied every frame
	void SetPosition(glm::vec3 position);
	// Set the position of the object
	// Position is automatically applied every frame
	// @param position Vector3 with position
	void SetPosition(float x, float y, float z);
	// Set the position of the object
	// Position is automatically applied every frame
	// @param x X float value
	// @param y Y float value
	// @param z Z float value
	void SetRotation(glm::vec3 rotation);
	// Set the position of the object
	// Position is automatically applied every frame
	void SetRotation(float x, float y, float z);
	// Set the rotation of the object
	// Rotation is automatically applied every frame
	void SetScale(glm::vec3 scale);
	// Set the rotation of the object
	// Rotation is automatically applied every frame
	void SetScale(float x, float y, float z);

	// Rotate object round value
	void Rotate(glm::vec3 rotation);
	// Rotate object round value
	void Rotate(float x, float y, float z);
	// Set rotation relative to an object
	void LookAt(glm::vec3 pos);
	// Set rotation relative to an object
	void LookAt(glm::vec2 pos);
	// Set rotation relative to an object
	void LookAt(float x, float y, float z);

	// Get rotation degrees
	float GetDegrees();
	// Set rotation degrees
	void SetDegrees(float degrees);

	// Get current position
	glm::vec3 GetPosition();
	// Get current rotation
	glm::vec3 GetRotation();
	// Get current scale
	glm::vec3 GetScale();

private:
	glm::vec3 pos;
	glm::vec3 rota;
	glm::vec3 scale;

	float degrees = 0.0f;
};