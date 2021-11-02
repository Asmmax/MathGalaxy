#pragma once
#include "drawables/Node.hpp"
#include "glm/glm.hpp"

class Triangle : public Node
{
private:
	float _size;
	glm::vec4 _color;
public:
	Triangle(float size = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
	void draw();
};