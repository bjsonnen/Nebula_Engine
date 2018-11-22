#pragma once

#include "Mesh.h"
#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>
#include "Window.h"

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);

	// Used to change the position based on the user input
	void KeyControl(GLFWwindow* window, float deltaTime);
	// Used to change the rotation based on the user input
	void MouseControl(float xChange, float yChange);

	// Set camera velocity
	void SetVelocity(float value);
	// Set camera turn speed
	void SetTurnSpeed(float value);
	// Set camera positon
	void SetPosition(glm::vec3 pos);

	// Look at a point
	void SetTarget(glm::vec3 pos);
	// Set fps editor camera on or off
	void SetStandardCamera(bool value);

	// Set nearest visible object
	void SetNear(float value);
	// Set farest visible object
	void SetFar(float value);

	// Get nearest visible object as float
	float GetNear();
	// Get farest visible object as float
	float GetFar();

	// Returns velocity
	float GetVelocity();
	// Returns camera rotation speed
	float GetTurnSpeed();

	// get the current camera position
	glm::vec3 GetCameraPosition();
	// Get the current camera direction
	glm::vec3 GetCameraDirection();

	// Calculate current view matrix
	glm::mat4 CalculateViewMatrix();

	~Camera();

private:
	// Update front, up and position
	void Update();

private:
	glm::vec3 dir = glm::vec3();
	glm::vec3 position  = glm::vec3();
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float moveSpeed;
	float turnSpeed;

	float near, far;
	float fov;

	bool standardCamera = true;
};

