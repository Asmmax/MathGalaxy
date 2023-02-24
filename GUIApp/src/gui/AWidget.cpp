#include "gui/AWidget.hpp"
#include "imgui.h"

AWidget::AWidget(const std::string& name, int width, int height):
	_name(name),
	_parent(nullptr),
	_isVisible(true),
	_width(width),
	_height(height)
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
			setupAsChild();
		}
		else {
			setupAsRoot();
		}
	}
}

void AWidget::setupAsChild()
{
	ImGui::BeginChild(_name.c_str(), ImVec2(static_cast<float>(_width), static_cast<float>(_height)), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
	setupContent();
	ImGui::EndChild();
}

void AWidget::setupAsRoot()
{
	if (_width != 0 || _height != 0) {
		ImGui::SetNextWindowSize(ImVec2(static_cast<float>(_width), static_cast<float>(_height)), ImGuiCond_Once);
		ImGui::Begin(_name.c_str());
	}
	else {
		ImGui::Begin(_name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	}
	setupContent();
	ImGui::End();
}
