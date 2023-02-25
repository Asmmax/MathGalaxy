#pragma once
#include "Node.hpp"
#include "glm/glm.hpp"

class Light : public Node
{
public:
	void init() override;
	void predraw(DrawContext& context) override;
	void draw(DrawContext& context) override;

	static int MAX_LIGHT_COUNT;
};