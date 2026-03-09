#include "gui/widgets/ViewportWidget.hpp"
#include "resources/Texture.hpp"
#include "View.hpp"
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

	using TexturePtr = std::conditional_t<sizeof(void*) == sizeof(std::int32_t), std::int32_t, std::int64_t>;
	TexturePtr fboTexture64 = static_cast<TexturePtr>(_view->getFboTexture()->getId().value);
	drawList->AddImage((void*)fboTexture64,
		pos,
		ImVec2(pos.x + size.x, pos.y + size.y),
		ImVec2(0, 1),
		ImVec2(1, 0));
}
