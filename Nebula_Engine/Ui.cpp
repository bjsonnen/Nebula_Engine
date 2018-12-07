#include "Ui.h"

Ui::Ui()
{
}


void Ui::DebugWindow(bool active, int fps, float deltaTime)
{
	if (!active)
		return;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open scene"))
			{
				// ToDo open scene
			}
			if (ImGui::MenuItem("Save scene"))
			{
				// ToDo save scene
			}
			if (ImGui::MenuItem("Close scene"))
			{
				// ToDo close scene
			}
			if (ImGui::MenuItem("Close engine"))
			{
				// ToDo close engine
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo"))
			{
				// ToDo
			}
			if (ImGui::MenuItem("Redo"))
			{
				// ToDo
			}
			if (ImGui::MenuItem("Lock debug window"))
			{
				// ToDo
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObject"))
		{
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Cube"))
				{
					// ToDo
				}
				if (ImGui::MenuItem("Sphere"))
				{
					// ToDo
				}
				if (ImGui::MenuItem("Plane"))
				{
					// ToDo
				}
				if (ImGui::MenuItem("Custom.."))
				{
					// ToDo
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Light"))
			{
				if (ImGui::MenuItem("Point"))
				{
					// ToDo
				}
				if (ImGui::MenuItem("Spot"))
				{
					// ToDo
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Audio"))
			{
				if (ImGui::MenuItem("2D"))
				{
					// ToDo
				}
				if (ImGui::MenuItem("3D"))
				{
					// ToDo
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Performance informations"))
			{
				showPerformanceWindow = true;
			}
			if (ImGui::MenuItem("General settings"))
			{
				showGeneralSettings = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About Nebula"))
			{
				// Open website with default webbrowser
				system("start http://www.google.com/");
			}
			if (ImGui::MenuItem("Nebula Manual"))
			{
				// Open website with default webbrowser
				system("start http://www.google.com/");
			}
			if (ImGui::MenuItem("Nebula Scripting Reference"))
			{
				// Open website with default webbrowser
				system("start http://www.google.com/");
			}
			ImGui::EndMenu();
		}
		ImGui::Text("|| %.3f ms/frame | (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();

		fpsCountIndex++;
		if (fpsCountIndex == 20)
			fpsCountIndex = 0;
		fpsCount[fpsCountIndex] = fps;

		PerformanceInformations();
		GeneralSettings();
	}
}

void Ui::PerformanceInformations()
{
	if (showPerformanceWindow)
	{
		ImGui::Begin("Performance Informations", &showPerformanceWindow);
		const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
		ImGui::PlotLines("FPS(20 secs)", fpsCount, 20);
		ImGui::PlotLines("deltaTime(20 frames)", my_values, IM_ARRAYSIZE(my_values));
		ImGui::End();
	}
}

void Ui::GeneralSettings()
{
	if (showGeneralSettings)
	{
		ImGui::Begin("General Settings", &showGeneralSettings);
		ImGui::Text("Light color: ");
		ImGui::SameLine();
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_RGB);
		ImGui::ColorEdit3("", (float*)&mainLightColor);
		ImGui::End();
	}
}

void Ui::Text(std::string text)
{
	ImGui::Text(text.c_str());
}

void Ui::Checkbox(std::string text, bool& output)
{
	ImGui::Checkbox(text.c_str(), &output);
}

Ui::~Ui()
{
}