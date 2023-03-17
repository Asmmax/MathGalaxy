#include "gui/widgets/ViewportWidget.hpp"
#include "infrastruct/View.hpp"
#include "imgui.h"

ViewportWidget::ViewportWidget(const std::string& name, int width, int height, View* view):
	AWidget(name, width, height),
	_view(view)
{
}

void ViewportWidget::setupContent()
{
	if (!_view) {
		return;
	}

	auto size = ImGui::GetContentRegionAvail();
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	_view->setSize(static_cast<int>(size.x), static_cast<int>(size.y));
	auto fboTexture64 = _view->getFBOTextureId();
	drawList->AddImage((void*)fboTexture64,
		pos,
		ImVec2(pos.x + size.x, pos.y + size.y),
		ImVec2(0, 1),
		ImVec2(1, 0));
}
