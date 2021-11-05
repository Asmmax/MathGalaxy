#pragma once
#include "drawables/Node.hpp"
#include "glm/glm.hpp"
#include <vector>

class Sphere : public Node
{
private:
	float _radius;
	unsigned int _segCount;
	glm::vec4 _color;
public:
	Sphere(float radius = 1.0f, unsigned int segCount = 20, const glm::vec4& color = glm::vec4(1.0f));
	void draw();

private:
	static void createGeosphere(float fStart, float fEnd, int nSegs, float radius, std::vector<glm::vec3>& vertices, std::vector<unsigned short>& indexes);
};
