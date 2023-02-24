#pragma once
#include "AMesh.hpp"

class Triangle : public AMesh
{
private:
	float _size;

public:
	Triangle(float size = 1.0f);

	size_t getIndicesCount() override;

protected:
	void generateMesh(std::vector<glm::vec3>& vertices, std::vector<unsigned short>& indices) override;
};