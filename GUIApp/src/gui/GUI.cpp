#include "gui/AWidget.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/GUI.hpp"
#include "infrastruct/IGraphicsContext.hpp"
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


void GUI::init(const std::weak_ptr<IGraphicsContext>& context)
{
	auto sharedContext = context.lock();
	if (_graphicsContext.lock() == sharedContext) {
		return;
	}

	_graphicsContext = context;

	if (!sharedContext) {
		return;
	}
	sharedContext->makeCurrent();

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
