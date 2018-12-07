#include "Ui.h"



Ui::Ui()
{
}


Ui::~Ui()
{
}

void Ui::Text(std::string text)
{
	ImGui::Text(text.c_str());
}

void Ui::Checkbox(std::string text, bool& output)
{
	ImGui::Checkbox(text.c_str(), &output);
}
