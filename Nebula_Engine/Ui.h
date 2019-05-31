#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Window.h"
#include "Texture.h"
#include "GameObject.h"

#include <stdio.h>
#include <string>

namespace NE
{

	//! Main class for the imgui ui system
	class Ui
	{
	public:
		//! Create ui object with standard parameters
		//!
		Ui();
		//! Create ui object with specific parameters
		//! @param window Insert main Window object as Window pointer
		Ui(NE::Window* window);

		//! Create a new Window
		//! Ui::EndWindow() need to be called
		//! @param text Insert title window as std::string
		void CreateWindow(std::string text);
		//! Close the window
		//! Need to be called
		void EndWindow();

		//! Create a single text line
		//! @param text Insert text as std::string
		void Text(std::string text);
		//! Create a textbox
		//! @param text Insert text as std::string
		//! @param output Insert reference to std::string as output
		void TextBox(std::string text, std::string& output);
		//! Create a checkbox
		//! @param text Insert text as std::string
		//! @param output Insert reference to bool as output
		void Checkbox(std::string text, bool& output);

		//! Returns true if mouse is over any ui element
		//! @return Returns bool 
		bool MouseOverUi();

		//! Specify if the next method should be in the same line
		void SameLine();

		//! Create the debug window
		//! @param active Insert enabled as bool
		//! @param fps Insert fps as int
		//! @param deltaTime Insert deltaTime as float
		//! @see Window::GetDeltaTime()
		//! @see Window::GetFPS()
		void DebugWindow(bool active, int fps, float deltaTime);

		~Ui();

	private:
		//! Used for PerformanceInformations();
		float fpsCount[20];
		int fpsCountIndex = 0;

		//! Used for PerformanceInformations();
		float deltaCount[20];
		int deltaCountIndex = 0;

		float cTime = 0.0f;
		float time = 0.0f;

		bool showPerformanceWindow = false;
		bool showGeneralSettings = false;
		bool showOpenScene = false;
		bool showCreateGameObject = false;
		bool showCreateLightObject = false;

		bool showDebugWindow = false;
		bool firstChange = false;

		//! GameObject informations
		float position[3] = { 0.0f, 0.0f, 0.0f };
		float rotation[3] = { 0.0f, 0.0f, 0.0f };
		float scale[3] = { 1.0f, 1.0f, 1.0f };
		char dTexture[100] = { "C:/" };
		char nTexture[100] = { "C:/" };
		char* name = "Object 1";
		char oneByte[100] = {};

		//! Light informations
		float lightPosition[3] = { 0.0f };
		float lightRotation[3] = { 0.0f };
		float lightColor[3] = { 1.0f };
		float lightIntensity = 1.0f;

		NE::GameObject go = NE::GameObject();

		ImVec4 mainLightColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		NE::Window* mainWindow = nullptr;
	};
}