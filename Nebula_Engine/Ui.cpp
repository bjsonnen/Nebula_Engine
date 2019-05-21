#include "Ui.h"

Ui::Ui()
{
}

Ui::Ui(Window* window)
{
	mainWindow = window;
}

void Ui::CreateWindow(std::string text)
{
	ImGui::Begin(text.c_str());
}

void Ui::EndWindow()
{
	ImGui::End();
}

bool Ui::MouseOverUi()
{
	return ImGui::IsMouseHoveringAnyWindow();
}

void Ui::SameLine()
{
	ImGui::SameLine();
}

void Ui::DebugWindow(bool active, int fps, float deltaTime)
{
	// Lock debug window
	if (!firstChange)
	{
		showDebugWindow = active;
		firstChange = true;
	}

	if (!active || !showDebugWindow)
		return;

	// Header menu
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::Text("%.3f ms/frame | (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();

		fpsCountIndex++;
		if (fpsCountIndex == 20)
			fpsCountIndex = 0;
		fpsCount[fpsCountIndex] = fps;
	}
}

void Ui::Text(std::string text)
{
	ImGui::Text(text.c_str());
}

void Ui::TextBox(std::string text, std::string& output)
{
	char* test = "";
	ImGui::InputText(text.c_str(), test, sizeof(test));
	output = test;

}

void Ui::Checkbox(std::string text, bool& output)
{
	ImGui::Checkbox(text.c_str(), &output);
}

Ui::~Ui()
{
}
