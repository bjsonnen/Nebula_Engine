#include "Camera.h"

NE::Camera::Camera()
{

}

NE::Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startRotationSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startRotationSpeed;

	near = 0.1f;
	far = 100.0f;

	Update();
}

NE::Camera::Camera(Vector3 startPosition, Vector3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed)
{
	position = glm::vec3(startPosition.x, startPosition.y, startPosition.z);
	worldUp = glm::vec3(startUp.x, startUp.y, startUp.z);
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	near = 0.1f;
	far = 100.0f;

	Update();
}

void NE::Camera::KeyControl(GLFWwindow * window, float deltaTime)
{
	if (!(standardCamera) || disableKeyMovement)
		return;

	Window* glfwwindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	float velocity = moveSpeed * deltaTime;

	if (glfwwindow->Key(Window::KeyCode::Left_Shift))
		velocity *= 2;

	if (glfwwindow->Key(Window::KeyCode::Q))
		position += up * velocity;

	if (glfwwindow->Key(Window::KeyCode::E))
		position -= up * velocity;

	if (glfwwindow->Key(Window::KeyCode::W))
		position += front * velocity;

	if (glfwwindow->Key(Window::KeyCode::S))
		position -= front * velocity;

	if (glfwwindow->Key(Window::KeyCode::A))
		position -= right * velocity;

	if (glfwwindow->Key(Window::KeyCode::D))
		position += right * velocity;
}

void NE::Camera::MouseControl(float xChange, float yChange)
{
	if (!(standardCamera) || disabledMouseMovement)
		return;

	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Update();
}

void NE::Camera::SetVelocity(float value)
{
	moveSpeed = value;
}

void NE::Camera::SetTurnSpeed(float value)
{
	turnSpeed = value;
}

void NE::Camera::SetPosition(glm::vec3 pos)
{
	position = pos;
}

void NE::Camera::SetPosition(Vector3 pos)
{
	position = glm::vec3(pos.x, pos.y, pos.z);
}

void NE::Camera::SetTarget(glm::vec3 object)
{
	dir = object;
}

void NE::Camera::SetTarget(Vector3 pos)
{
	dir = glm::vec3(pos.x, pos.y, pos.z);
}

void NE::Camera::SetStandardCamera(bool value)
{
	standardCamera = value;
}

void NE::Camera::SetNear(float value)
{
	near = value;
}

void NE::Camera::SetFar(float value)
{
	far = value;
}

float NE::Camera::GetNear()
{
	return near;
}

float NE::Camera::GetFar()
{
	return far;
}

void NE::Camera::DisableMouseMovement(bool value)
{
	disabledMouseMovement = value;
}

bool NE::Camera::GetDisableMouseMovement()
{
	return disabledMouseMovement;
}

void NE::Camera::DisableKeyMovement(bool value)
{
	disableKeyMovement = value;
}

bool NE::Camera::GetDisableKeyMovement()
{
	return disableKeyMovement;
}

float NE::Camera::GetVelocity()
{
	return moveSpeed;
}

float NE::Camera::GetTurnSpeed()
{
	return turnSpeed;
}

glm::mat4 NE::Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 NE::Camera::GetCameraPosition()
{
	return position;
}
Vector3 NE::Camera::GetCameraPositionVector3()
{
	return position;
}
glm::vec3 NE::Camera::GetCameraDirection()
{
	return glm::normalize(front);
}

void NE::Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	// Set target
	if (dir != glm::vec3())
	{
		front = position - dir;
		dir = glm::vec3();
	}

	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


NE::Camera::~Camera()
{
}
