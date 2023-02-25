#pragma once
#include "drawables/Node.hpp"
#include <memory>
#include <vector>

class Group : public Node
{
private:
	std::vector<std::shared_ptr<Node>> _children;
public:
	void addChild(const std::shared_ptr<Node>& child);
	unsigned int getChildCount() const;
	std::shared_ptr<Node> getChild(unsigned int id) const;

	void init() override;
	void predraw(DrawContext& context) override;
	void draw(DrawContext& context) override;
};