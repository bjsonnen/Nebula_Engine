#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Window.h"
#include "Texture.h"

#include <stdio.h>
#include <string>

class Ui
{
public:
	Ui();
	Ui(Window* window);

	// Create a new Window
	// Ui::EndWindow() need to be called!
	void CreateWindow(std::string text);
	// Close the window
	// Need to be called!
	void EndWindow();

	// Create a single text line
	void Text(std::string text);
	// Create a textbox
	void TextBox(std::string text, std::string& output);
	// Create a checkbox
	// bool is the output
	void Checkbox(std::string text, bool& output);
	// Create a single slider
	// 2. parameter is the output
	void Slider(std::string text, float& value, float min, float max);
	// Create a color change box
	// last 3 parameters are the output
	void ColorEdit3(std::string text, float& x, float& y, float& z);
	// Create a single button
	void Button();

	// Returns true if mouse is over any ui element
	bool MouseOverUi();

	// Specify if the next method should be in the same line
	void SameLine();

	// Create the debug window
	void DebugWindow(bool active, int fps, float deltaTime);

	~Ui();

private:
	void DebugFile();
	void DebugEdit();
	void DebugGameObject();
	void DebugWindow();
	void DebugHelp();

	void PerformanceInformations();
	void GeneralSettings();

	void OpenScene();

	void CreateGameObject();
	void CreateLightObject();

private:
	// Used for PerformanceInformations();
	float fpsCount[20];
	int fpsCountIndex = 0;

	// Used for PerformanceInformations();
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

	// GameObject informations
	float position[3] = { 0.0f };
	float rotation[3] = { 0.0f };
	float scale[3] = { 1.0f };
	char dTexture[100] = {"C:/"};
	char nTexture[100] = {"C:/"};
	char* name = "GameObject 1";
	char oneByte[100] = {};

	// Light informations
	float lightPosition[3] = { 0.0f };
	float lightRotation[3] = { 0.0f };
	float lightColor[3] = { 1.0f };
	float lightIntensity = 1.0f;


	ImVec4 mainLightColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	Window* mainWindow = nullptr;
};