#include "gui/menu/MenuItemEnabler.hpp"
#include "gui/AWidget.hpp"

MenuItemEnabler::MenuItemEnabler(const std::string& name, const std::weak_ptr<AWidget>& widget):
	AMenuItem(name),
	_widget(widget)
{
}

void MenuItemEnabler::click()
{
	auto widgetPtr = _widget.lock();

	if (widgetPtr) {
		widgetPtr->setVisible(!widgetPtr->getVisible());
	}
}
