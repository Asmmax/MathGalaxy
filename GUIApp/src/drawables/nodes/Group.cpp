#include "drawables/nodes/Group.hpp"
#include "drawables/Transform.hpp"
#include "infrastruct/DrawContext.hpp"

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

void Group::init(const std::weak_ptr<IGraphicsContext>& context)
{
	if (_graphicsContext.lock() == context.lock()) {
		return;
	}

	deinit();
	_graphicsContext = context;

	for (auto child : _children)
	{
		child->init(_graphicsContext);
	}
}

void Group::deinit()
{
	if (_graphicsContext.expired()) {
		return;
	}

	for (auto child : _children)
	{
		child->deinit();
	}

	_graphicsContext.reset();
}

void Group::predraw(DrawContext& context)
{
	for (auto child : _children)
	{
		child->predraw(context);
	}
}

void Group::draw(const DrawContext& context)
{
	for (auto& child : _children) 
	{
		child->draw(context);
	}
}

void Group::addChild(const std::shared_ptr<Node>& child)
{
	if (!child) {
		return;
	}

	getTransform()->addChild(child->getTransform());
	_children.emplace_back(child);

	if (!_graphicsContext.expired()) {
		child->init(_graphicsContext);
	}
}

void Group::removeChild(const std::shared_ptr<Node>& child)
{
	if (!child) {
		return;
	}

	getTransform()->removeChild(child->getTransform());
	auto lastIt = std::remove(_children.begin(), _children.end(), child);
	_children.erase(lastIt, _children.end());
}
