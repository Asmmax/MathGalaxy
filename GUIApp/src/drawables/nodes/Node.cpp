#include "drawables/nodes/Node.hpp"
#include "drawables/Transform.hpp"
#include "drawables/nodes/Group.hpp"

Node::Node():
	_transform(std::make_shared<Transform>())
{
}

void Node::setParent(const std::weak_ptr<Group>& parent)
{
	if (auto parentShared = _parent.lock()) {
		parentShared->removeChild(shared_from_this());
	}

	_parent = parent;

	if (auto parentShared = _parent.lock()) {
		parentShared->addChild(shared_from_this());
	}
}
