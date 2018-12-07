#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <stdio.h>
#include <string>

class Ui
{
public:
	Ui();

	// Create a new Window
	// Ui::EndWindow() need to be called!
	void CreateWindow();
	// Close the window
	// Need to be called!
	void EndWindow();

	void Text(std::string text);
	void Checkbox(std::string text, bool& output);
	void ShowWindow(bool value);
	void Slider(std::string text, float& value, float min, float max);
	void ColorEdit3(std::string text, float& x, float& y, float& z);
	void Button();

	void SameLine();

	~Ui();
};

