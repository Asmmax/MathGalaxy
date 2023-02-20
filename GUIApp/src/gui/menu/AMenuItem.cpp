#include "gui/menu/AMenuItem.hpp"
#include "imgui.h"

AMenuItem::AMenuItem(const std::string& name):
	_name(name),
	_shortcut(),
	_isEnabled(true)
{
}

void AMenuItem::enable()
{
	_isEnabled = true;
}

void AMenuItem::disable()
{
	_isEnabled = false;
}

void AMenuItem::setup()
{
	if (ImGui::MenuItem(_name.c_str(), _shortcut.empty() ? nullptr : _shortcut.c_str(), false, _isEnabled))
	{
		click();
	}
}