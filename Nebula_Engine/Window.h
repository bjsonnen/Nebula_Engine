#pragma once

#include "stdio.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <string>
#include "CommonValues.h"

class Window
{
public:
	Window();

#pragma region KeyCodeDefinition
	// KeyCode definitions for key handling
	enum KeyCode
	{
		Q = 81,
		W = 87,
		E = 69,
		R = 82,
		T = 84,
		Z = 90,
		U = 85,
		O = 79,
		P = 80,
		A = 65,
		S = 83,
		D = 68,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		Y = 89,
		X = 88,
		C = 67,
		V = 86,
		B = 66,
		N = 78,
		M = 77,
		Escape = 256,
		Left_Shift = 340
	};
#pragma endregion

#pragma region KeyActionDefinitions
	// KeyAction definitions for key action handling
	enum KeyAction
	{
		KeyDown = GLFW_PRESS,
		KeyUp = GLFW_RELEASE,
		KeyRepeat = GLFW_REPEAT
	};
#pragma endregion
	
	Window(int windowWidth, int windowHeight);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	// Intialise the window
	int Initialise();
	
	int GetBufferWidth() { return bufferWidth; }
	int GetBufferHeight() { return bufferHeight; }

	int GetWindowWidth();
	int GetWindowHeight();

	// Returns current fps (every 1s update)
	int GetFPS();
	// Returns deltaTime
	float GetDeltaTime();

	// If window should close
	bool GetShouldClose();

	// Switch from pologon to wireframe
	void SetWireframe(bool value);

	// Returns current wireframe mode via bool
	bool GetWireframe();

	float GetTime();

	// Show or hide mouse
	void ShowMouse(bool value);
	// Switch (for ex.) from show to hide
	void SwitchMouse();
	// Set refresh rate
	void SetRefreshRate(int value);
	// Get refresh rate
	int GetRefreshRate();
	// Get mouse setting (bool)
	bool GetShowMouse();

	void SetPerspectiveMode(int x);
	int GetPerspectiveMode();

	glm::mat4 CalculateProjectionMatrix(float fovy, float aspect, float zNear, float zFar);

	// Close the game
	void CloseWindow();

	// Set icon of window
	// WARNING -> Extreme performance loss
	void SetIcon(std::string file);

	// Enable msaa
	void SetMsaa(bool value, int filters);
	// Get msaa bool
	bool GetMsaa();

	// Change title of the game
	void SetTitle(std::string title);

	// Set Vertical Synchronisation
	void SetVSync(bool value);
	// Switch Vertical Synchronisation
	void SwitchVSync();
	// Get Vertical Synchronisation (bool)
	bool GetVSync();
	
	// Returns mouse X change
	float GetXChange();
	// Returns mouse Y change
	float GetYChange();

	// Returns a pointer to the window object
	GLFWwindow* GetWindow()
	{
		return mainWindow;
	}

	// Returns true if <key> is pressed
	bool Key(KeyCode key);
	// Returns true if <key> is <action>
	bool Key(KeyCode key, KeyAction action);

	// Called every frame
	// Used for ESCAPE & change renderer size
	void WindowUpdate();

	// Swap Buffers (Swap Chain)
	void SwapBuffers();

	~Window();

private:
	GLFWwindow* mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	// Camera informations
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	float lastTime = 0.0f;
	float deltaTime = 0.0f;
	int refreshRate = 0;

	float previousTime = 0.0f;
	int frameCount = 0;
	int fps = 0;

	int perspectiveMode = 1;

	void createCallbacks();
	// Used to simulate camera movement
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);

	// Window information
	bool showMouse = true;
	bool vsync = false;
	bool msaa = true;

	int msaaFilters = 4;
	bool wireframe = false;
};