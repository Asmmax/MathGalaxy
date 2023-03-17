#include "gui/AWidget.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/GUI.hpp"
#include "imgui.h"
#include "gl/gl_core_4_3.hpp"
#include "GLFW/glfw3.h"

void GUI::addWidget(const std::shared_ptr<AWidget>& child)
{
	if (!child) {
		return;
	}

	_children.emplace_back(child);
}

void GUI::setMenu(const std::shared_ptr<MenuPanel>& menu)
{
	_menu = menu;
}


void GUI::init()
{
	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void GUI::setup()
{
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	for (auto& child : _children)
	{
		child->setup();
	}

	if (_menu) {
		_menu->setup();
	}

}
