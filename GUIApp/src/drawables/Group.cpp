#include "drawables/Group.hpp"
#include "Transform.hpp"
#include "DrawContext.hpp"

void Group::addChild(const std::shared_ptr<Node>& child)
{
	getTransform()->addChild(child->getTransform());
	_children.emplace_back(child);
}

unsigned int Group::getChildCount() const
{
	return static_cast<unsigned int>(_children.size());
}
std::shared_ptr<Node> Group::getChild(unsigned int id) const
{
	return _children[id];
}

void Group::init()
{
	for (auto child : _children)
	{
		child->init();
	}
}

void Group::predraw(DrawContext& context)
{
	for (auto child : _children)
	{
		child->predraw(context);
	}
}

void Group::draw(DrawContext& context)
{
	if (_children.empty()) {
		return;
	}

	if (_children.size() == 1) {
		_children.front()->draw(context);
		return;
	}

	DrawContext origin(context);
	for (auto it = _children.begin(); it != _children.end(); it++) {
		if (it != _children.begin()) {
			context = origin;
		}
		(*it)->draw(context);
	}
}
