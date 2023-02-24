#pragma once
#include "glm/glm.hpp"
#include <vector>

class AMesh
{
private:
	unsigned int _vaoHandle;

public:
	AMesh();
	virtual ~AMesh() {}

	void init();
	void draw();

	virtual size_t getIndicesCount() = 0;

protected:
	virtual void generateMesh(std::vector<glm::vec3>& vertices, std::vector<unsigned short>& indices) = 0;
};
