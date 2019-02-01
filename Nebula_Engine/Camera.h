#pragma once

#include "Mesh.h"
#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>
#include "Window.h"

//! Camera main class
class Camera
{
public:
	//! Creates a camera with standard parameters
	//!
	Camera();
	//! Creates a camera with specific parameters
	//! @param startPosition Insert the start Position as glm::vec3
	//! @param startUp Insert the start up vector3 as glm::vec3
	//! @param startYaw Insert the start yaw as float
	//! @param startPitch Insert the start pitch as float
	//! @param startMoveSpeed Insert the start move speed of the camera as float
	//! @param startTurnSpeed Insert the start turn speed of the camera as float
	Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);
	//! Creates a camera with specific parameters
	//! @param startPosition Insert the start Position as Vector3
	//! @param startUp Insert the start up vector3 as Vector3
	//! @param startYaw Insert the start yaw as float
	//! @param startPitch Insert the start pitch as float
	//! @param startMoveSpeed Insert the start move speed of the camera as float
	//! @param startTurnSpeed Insert the start turn speed of the camera as float
	Camera(Vector3 startPosition, Vector3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);

	//! Used to change the position based on the user input
	//! @param window Insert a GLFWwindow pointer (internal)
	//! @param deltaTime Insert a float value for delta time.
	//! @see Window::GetDeltaTime()
	void KeyControl(GLFWwindow* window, float deltaTime);
	//! Used to change the rotation based on the user input
	//! @param xChange Change of the x mouse position
	//! @param yChange Change of the y mouse position
	void MouseControl(float xChange, float yChange);

	//! Set camera velocity
	//! @param value Set the velocity of the camera as float
	void SetVelocity(float value);
	//! Set camera turn speed
	//! @param value Set the turn speed of the camera as float
	void SetTurnSpeed(float value);
	//! Set camera positon
	//! @param pos Set the camera position as glm::vec3
	void SetPosition(glm::vec3 pos);
	//! Set camera positon
	//! @param pos Set the camera position as glm::vec3
	void SetPosition(Vector3 pos);

	//! Look at a point
	//! @param pos Set the focus point of the camera to a glm::vec3 position
	void SetTarget(glm::vec3 pos);
	//! Look at a point
	//! @param pos Set the focus point of the camera to a glm::vec3 position
	void SetTarget(Vector3 pos);
	//! Set fps editor camera on or off
	//! @param value Enable/Disable the standard camera
	void SetStandardCamera(bool value);

	//! Set nearest visible object
	//! @param value Insert distance from camera to near plane
	void SetNear(float value);
	//! Set farest visible object
	//! @param value Insert distance from camera to far plane
	void SetFar(float value);

	//! Get nearest visible object as float
	//! @return Returns the distance to the near plane as float
	float GetNear();
	//! Get farest visible object as float
	//! @return Returns the distance to the far plane as float
	float GetFar();

	//! Dis-/Enable mouse movement
	//! @param value Insert value as bool
	void DisableMouseMovement(bool value);
	//! Get if mouse movement is disabled
	//! @return Get bool if mouse movement is disabled
	bool GetDisableMouseMovement();

	//! Dis-/Enable key movement
	//! @param value Insert value as bool
	void DisableKeyMovement(bool value);
	//! Get if key movement is disabled
	//! @return Get bool if key movement is disabled
	bool GetDisableKeyMovement();

	//! Returns velocity
	//! @return Returns the velocity as float
	float GetVelocity();
	//! Returns camera rotation speed
	//! @return Returns the turn speed as float
	float GetTurnSpeed();

	//! Get the current camera position
	//! @return Returns the camera position as glm::vec3
	glm::vec3 GetCameraPosition();
	//! Get the current camera position
	//! @return Returns the camera position as Vector3
	Vector3 GetCameraPositionVector3();
	//! Get the current camera direction
	//! @return Returns the camera direction as glm::vec3
	glm::vec3 GetCameraDirection();
	//! Get the current camera position
	//! @return Returns the camera position as Vector3
	Vector3 GetCameraDirectionVector3();

	//! Calculate current view matrix
	//! @return Returns the view matrix as 4x4 matrix (glm::mat4)
	glm::mat4 CalculateViewMatrix();

	~Camera();

private:
	//! Update front, up and position
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
	bool disabledMouseMovement = false;
	bool disableKeyMovement = false;
};

