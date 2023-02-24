#pragma once
#include "glm/glm.hpp"

struct DrawContext
{
	glm::mat4x4 viewMatrix;
	glm::mat4x4 projectionMatrix;
};

class IDrawable
{
public:
	virtual ~IDrawable() {}
	virtual void init() = 0;
	virtual void draw(const DrawContext& context) = 0;
};