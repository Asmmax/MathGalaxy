#include "gui/AWidget.hpp"
#include "imgui.h"

AWidget::AWidget(const std::string& name):
	_name(name),
	_parent(nullptr),
	_isVisible(true)
{
}

void AWidget::setParent(AWidget* parent)
{
	_parent = parent;
}

void AWidget::setVisible(bool visible)
{
	_isVisible = visible;
}

void AWidget::setup()
{
	if (_isVisible) {
		if (_parent) {
			drawAsChild();
		}
		else {
			drawAsRoot();
		}
	}
}

void AWidget::drawAsChild()
{
	ImGui::BeginChild(_name.c_str(), ImVec2(200,100), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
	draw();
	ImGui::EndChild();
}

void AWidget::drawAsRoot()
{
	ImGui::Begin(_name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	draw();
	ImGui::End();
}
