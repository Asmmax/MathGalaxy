#pragma once
#include "AMesh.hpp"

class Sphere : public AMesh
{
private:
	float _radius;
	unsigned int _segCount;

public:
	Sphere(float radius = 1.0f, unsigned int segCount = 20);

	int getIndicesCount() override;

protected:
	void generateMesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<unsigned short>& indices) override;

private:
	static void createGeosphere(float fStart, float fEnd, int nSegs, float radius, std::vector<glm::vec3>& vertices, std::vector<unsigned short>& indexes);
};
