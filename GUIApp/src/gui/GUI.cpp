#include "gui/AWidget.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/GUI.hpp"

void GUI::addWidget(const std::shared_ptr<AWidget>& child)
{
	_children.emplace_back(child);
}

void GUI::setMenu(const std::shared_ptr<MenuPanel>& menu)
{
	_menu = menu;
}

void GUI::setup()
{
	for (auto& child : _children)
	{
		child->setup();
	}

	if (_menu) {
		_menu->setup();
	}
}
