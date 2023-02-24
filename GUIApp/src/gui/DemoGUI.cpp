#include "gui/DemoGUI.hpp"
#include "imgui.h"

void DemoGUI::init()
{
	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void DemoGUI::setup()
{
	ImGui::ShowDemoWindow();
}
