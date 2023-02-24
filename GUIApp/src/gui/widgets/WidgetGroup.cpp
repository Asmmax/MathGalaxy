#include "gui/widgets/WidgetGroup.hpp"
#include "gui/AWidget.hpp"

WidgetGroup::WidgetGroup(const std::string& name, int width, int height):
	AWidget(name, width, height)
{
}

void WidgetGroup::addChild(const std::shared_ptr<AWidget>& widget)
{
	_children.push_back(widget);
	widget->setParent(this);
}

void WidgetGroup::setupContent()
{
	for (auto& child : _children) {
		child->setup();
	}
}
