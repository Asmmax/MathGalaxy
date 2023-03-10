#include "gui/DemoGUI.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include "imgui.h"

void DemoGUI::init(const std::weak_ptr<IGraphicsContext>& context)
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

void DemoGUI::setup()
{
	ImGui::ShowDemoWindow();
}
