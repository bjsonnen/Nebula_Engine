#include "Ui.h"

NE::Ui::Ui()
{
}

NE::Ui::Ui(NE::Window* window)
{
	mainWindow = window;
}

void NE::Ui::CreateWindow(std::string text)
{
	ImGui::Begin(text.c_str());
}

void NE::Ui::EndWindow()
{
	ImGui::End();
}

bool NE::Ui::MouseOverUi()
{
	return ImGui::IsMouseHoveringAnyWindow();
}

void NE::Ui::SameLine()
{
	ImGui::SameLine();
}

void NE::Ui::DebugWindow(bool active, int fps, float deltaTime)
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

void NE::Ui::Text(std::string text)
{
	ImGui::Text(text.c_str());
}

void NE::Ui::TextBox(std::string text, std::string& output)
{
	char* test = "";
	ImGui::InputText(text.c_str(), test, sizeof(test));
	output = test;

}

void NE::Ui::Checkbox(std::string text, bool& output)
{
	ImGui::Checkbox(text.c_str(), &output);
}

NE::Ui::~Ui()
{
}
