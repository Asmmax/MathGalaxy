#include "drawables/Node.hpp"
#include "Transform.hpp"

Node::Node():
	_transform(std::make_shared<Transform>())
{
}
