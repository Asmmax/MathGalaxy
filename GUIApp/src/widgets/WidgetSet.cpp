#include "widgets/WidgetSet.hpp"

void WidgetSet::addChild(const std::shared_ptr<IWidget>& child)
{
	_children.emplace_back(child);
}

void WidgetSet::setup()
{
	for (auto& child : _children)
	{
		child->setup();
	}
}
