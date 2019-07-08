#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>

#include "stdio.h"
#include "CommonValues.h"
#include "Util.h"

namespace NE
{
	//! Main class to create the window, resize window and key/mouse inputs
	class Window
	{
	public:
		//! Create a window with 800x600 pixels
		Window();

#pragma region KeyCodeDefinition
		//! KeyCode definitions for key handling
		//!
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
		//! KeyAction definitions for key action handling
		//!
		enum KeyAction
		{
			KeyDown = GLFW_PRESS,
			KeyUp = GLFW_RELEASE,
			KeyRepeat = GLFW_REPEAT
		};
#pragma endregion

		//! Create a window with specific width and height
		//! @param windowWidth Insert window width for the window
		//! @param windowHeight Insert window height for the window
		Window(int windowWidth, int windowHeight);

		//! Change framebuffer size
		//! @param window Insert GLFWwindow pointer (internal)
		//! @param width Insert new window width as int
		//! @param height Insert new window height as int
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		//! Intialise the window
		//! @return Returns a NE_ERROR
		//! @see NE_ERROR_CHECK
		NE_ERROR Initialise();

		//! Get OpenGL Window width
		//! @return Returns the buffer width as int
		int GetBufferWidth() { return bufferWidth; }
		//! Get OpenGL Window height
		//! @return Returns the buffer height as int
		int GetBufferHeight() { return bufferHeight; }

		//! Get the current window width
		//! @return Returns the window width as int
		int GetWindowWidth();
		//! Get the current window height
		//! @return Returns the window height as int
		int GetWindowHeight();

		//! Returns current fps (every 1s update)
		//! @return Returns the fps as int
		int GetFPS();
		//! Returns deltaTime
		//! @return Returns the delta time as float
		float GetDeltaTime();

		//! If window should close
		//! @return Returns if the window should close
		bool GetShouldClose();

		//! Switch from pologon to wireframe
		//! @param value Insert bool if wireframed
		void SetWireframe(bool value);

		//! Returns current wireframe mode via bool
		//! @return Returns if the game in windowed
		bool GetWireframe();

		//! Get time
		//! @return Returns the time as float
		float GetTime();

		//! Show or hide mouse
		//! @param value Insert bool if mouse should be visible or hidden
		void ShowMouse(bool value);
		//! Switch (for ex.) from show to hide
		//!
		void SwitchMouse();
		//! Set refresh rate
		//! @param value Insert refreshrate per second as int
		void SetRefreshRate(int value);
		//! Get refresh rate
		//! @return Returns the refreshrate per second as int
		int GetRefreshRate();
		//! Get mouse setting (bool)
		//! @return Return a bool if mouse if visible
		bool GetShowMouse();

		//! Switch to Perspective/Orthografic mode
		//! 0 = Perspective
		//! 1 = Orthografic
		//! @param x Insert int to switch from one perspective to another
		void SetPerspectiveMode(int x);
		//! Get Perspective mode
		//! 0 = Perspective
		//! 1 = Orthografic
		//! @return Returns the current perspective mode as int
		int GetPerspectiveMode();

		//! Calculates projection matrix for the shader
		//! @param fovy Insert fovy value as float
		//! @param aspect Insert aspect value as float
		//! @param zNear Insert near plane as float
		//! @param zFar Insert far plane as float
		//! @return Return the projection matrix as 4x4 matrix
		glm::mat4 CalculateProjectionMatrix(float fovy, float aspect, float zNear, float zFar);

		//! Close the game
		void CloseWindow();

		//! Set icon of window
		//! WARNING -> Extreme performance loss
		//! @param file Insert file location as std::string
		void SetIcon(std::string file);

		//! Enable msaa
		//! @param value Enable/Diabale msaa as bool
		//! @param filters Pixel being filtered as int
		void SetMsaa(bool value, int filters);
		//! Get msaa bool
		//! @return Msaa bool
		bool GetMsaa();

		//! Change title of the game
		//! @param title Insert title as std::string
		void SetTitle(std::string title);

		//! Set Vertical Synchronisation
		//! @param value Enable vsync
		void SetVSync(bool value);
		//! Switch Vertical Synchronisation
		//!
		void SwitchVSync();
		//! Get Vertical Synchronisation (bool)
		//! @return vsync bool
		bool GetVSync();

		//! Returns mouse X change
		//! @return Returns mouse x change
		float GetXChange();
		//! Returns mouse Y change
		//! @return Returns mouse y change
		float GetYChange();

		//! Returns a pointer to the window object
		//! @return Returns a GLFWwindow pointer to the window object (internal)
		GLFWwindow* GetWindow() { return mainWindow; }

		//! Returns true if <key> is pressed
		//! @param key Insert KeyCode
		//! @return Returns bool
		//! @see KeyCode
		bool Key(KeyCode key);
		//! Returns true if <key> is <action>
		//! @param key Insert KeyCode
		//! @param action Insert KeyAction
		//! @return Returns bool
		//! @see KeyCode
		//! @see KeyAction
		bool Key(KeyCode key, KeyAction action);

		//! Called every frame
		//! Used for ESCAPE & change renderer size
		void WindowUpdate();

		//! Swap Buffers (Swap Chain)
		//!
		void SwapBuffers();

		~Window();

	private:
		GLFWwindow* mainWindow;

		int width, height;
		int bufferWidth, bufferHeight;

		//! Camera informations
		float lastX;
		float lastY;
		float xChange;
		float yChange;
		bool mouseFirstMoved;

		float lastTime = 0.0f;
		float deltaTime = 0.0f;
		int refreshRate = 0;

		float previousTime = 0.0f;
		int frameCount = 0;
		int fps = 0;

		int perspectiveMode = 1;

		void createCallbacks();
		//! Used to simulate camera movement
		static void HandleMouse(GLFWwindow* window, double xPos, double yPos);

		//! Window information
		bool showMouse = true;
		bool vsync = false;
		bool msaa = true;

		int msaaFilters = 4;
		bool wireframe = false;
	};
}

