#include "drawables/Group.hpp"
#include "Transform.hpp"

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

void Group::draw()
{
	for (auto child : _children)
	{
		child->draw();
	}
}
