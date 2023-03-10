#pragma once
#include "infrastruct/resources/AMesh.hpp"

class Triangle : public AMesh
{
private:
	float _size;

public:
	Triangle(float size = 1.0f);

	int getIndicesCount() override;

protected:
	void generateMesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<unsigned short>& indices) override;
};