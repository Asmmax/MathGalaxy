#pragma once
#include "glm/glm.hpp"

class IDrawable
{
public:
	virtual ~IDrawable() {}
	virtual void draw() = 0;
};