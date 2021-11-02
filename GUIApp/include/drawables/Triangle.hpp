#pragma once
#include "IDrawable.hpp"
#include "glm/glm.hpp"

class Triangle : public IDrawable
{
private:
	glm::mat4 _projectionMatrix;
public:
	Triangle();
	void draw() override;
};