#pragma once
#include "drawables/nodes/Node.hpp"
#include <memory>
#include <vector>

class Group : public Node
{
	friend Node;
private:
	std::vector<std::shared_ptr<Node>> _children;
	std::weak_ptr<IGraphicsContext> _graphicsContext;
public:
	void attachChild(const std::shared_ptr<Node>& child);
	unsigned int getChildCount() const;
	std::shared_ptr<Node> getChild(unsigned int id) const;

	void init(const std::weak_ptr<IGraphicsContext>& context) override;
	void deinit() override;
	void predraw(DrawContext& context) override;
	void draw(const DrawContext& context) override;

private:
	void addChild(const std::shared_ptr<Node>& child);
	void removeChild(const std::shared_ptr<Node>& child);
};