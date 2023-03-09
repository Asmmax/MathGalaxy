#include "drawables/Group.hpp"
#include "Transform.hpp"
#include "DrawContext.hpp"

void Group::attachChild(const std::shared_ptr<Node>& child)
{
	auto&& thisNode = shared_from_this();
	auto&& thisGroup = std::static_pointer_cast<Group>(thisNode);
	child->setParent(thisGroup);
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

void Group::addChild(const std::shared_ptr<Node>& child)
{
	getTransform()->addChild(child->getTransform());
	_children.emplace_back(child);
}

void Group::removeChild(const std::shared_ptr<Node>& child)
{
	getTransform()->removeChild(child->getTransform());
	auto lastIt = std::remove(_children.begin(), _children.end(), child);
	_children.erase(lastIt, _children.end());
}
