#pragma once
#include <glm/vec3.hpp>
#include <vector>

struct MeshData
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> indices;
};

const float pi = 3.1415926536f;

MeshData createTriangle(float size = 1.0f);
MeshData createSphere(float radius = 1.0f, unsigned int segCount = 20, float fStart = -pi / 2, float fEnd = pi / 2);
