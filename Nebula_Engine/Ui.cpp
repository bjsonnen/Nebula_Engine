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
		if (ImGui::BeginMenu("File"))
		{
			DebugFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			DebugEdit();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObject"))
		{
			DebugGameObject();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			DebugWindow();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			DebugHelp();
			ImGui::EndMenu();
		}
		ImGui::Text("|| %.3f ms/frame | (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();

		fpsCountIndex++;
		if (fpsCountIndex == 20)
			fpsCountIndex = 0;
		fpsCount[fpsCountIndex] = fps;

		OpenScene();

		CreateGameObject();
		CreateLightObject();

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

void Ui::OpenScene()
{
	if (showOpenScene)
	{
		ImGui::Begin("Open Scene...", &showOpenScene);
		Text("File: ");
		SameLine();
		TextBox("", std::string());
		ImGui::End();
	}
}

void Ui::CreateGameObject()
{
	if (showCreateGameObject)
	{
		ImGui::Begin("Create GameObject...", &showCreateGameObject);
		if (ImGui::TreeNode("Transform"))
		{
			ImGui::InputText("Name", oneByte, sizeof(char) * 100);
			ImGui::InputFloat3("Position", position);
			ImGui::InputFloat3("Rotation", rotation);
			ImGui::InputFloat3("Scale", scale);
			ImGui::TreePop();
		}
		ImGui::Separator();
		if (ImGui::TreeNode("Textures"))
		{
			ImGui::InputText("Diffuse Texture", dTexture, sizeof(char) * 100);
			ImGui::InputText("Normal Texture", nTexture, sizeof(char) * 100);
			ImGui::TreePop();
		}
		ImGui::Separator();
		if (ImGui::Button("Create GameObject"))
		{
			// Create gameobject
		}
		ImGui::Separator();
		ImGui::End();
	}
}

void Ui::CreateLightObject()
{
	if (showCreateLightObject)
	{
		ImGui::Begin("Create Light...", &showCreateLightObject);
		if (ImGui::TreeNode("Transform"))
		{
			ImGui::InputText("Name", oneByte, sizeof(char) * 100);
			ImGui::InputFloat3("Position", lightPosition);
			ImGui::InputFloat3("Rotation", lightRotation);
			ImGui::SliderFloat("Intensity", &lightIntensity, 0.0f, 1.0f);
			ImVec4 tmpColor = ImVec4(lightColor[0], lightColor[1], lightColor[2], 1.0f);
			ImGui::ColorEdit3("Light Color", (float*)&tmpColor);
			lightColor[0] = tmpColor.x;
			lightColor[1] = tmpColor.y;
			lightColor[2] = tmpColor.z;
			ImGui::TreePop();
		}
		ImGui::Separator();
		if (ImGui::Button("Create Light"))
		{
			// Create light
		}
		ImGui::End();
	}
}

void Ui::Text(std::string text)
{
	ImGui::Text(text.c_str());
}

void Ui::TextBox(std::string text, std::string& output)
{
	char* test;
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

void Ui::DebugFile()
{
	if (ImGui::MenuItem("Open scene"))
	{
		
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
		mainWindow->CloseWindow();
	}
}

void Ui::DebugEdit()
{
	if (ImGui::MenuItem("Undo"))
	{
		// ToDo
	}
	if (ImGui::MenuItem("Redo"))
	{
		// ToDo
	}
	if (ImGui::MenuItem("Disable debug window"))
	{
		showDebugWindow = false;
	}
}

void Ui::DebugGameObject()
{
	if (ImGui::BeginMenu("Create"))
	{
		if (ImGui::MenuItem("Cube"))
		{
			showCreateGameObject = true;
		}
		if (ImGui::MenuItem("Sphere"))
		{
			showCreateGameObject = true;
		}
		if (ImGui::MenuItem("Plane"))
		{
			showCreateGameObject = true;
		}
		if (ImGui::MenuItem("Custom.."))
		{
			showCreateGameObject = true;
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Light"))
	{
		if (ImGui::MenuItem("Point"))
		{
			showCreateLightObject = true;
		}
		if (ImGui::MenuItem("Spot"))
		{
			showCreateLightObject = true;
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
}

void Ui::DebugWindow()
{
	if (ImGui::MenuItem("Performance informations"))
	{
		showPerformanceWindow = true;
	}
	if (ImGui::MenuItem("General settings"))
	{
		showGeneralSettings = true;
	}
}

void Ui::DebugHelp()
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
}
