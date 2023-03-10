#pragma once
#include "glm/glm.hpp"
#include <memory>
#include <vector>

class IGraphicsContext;

class AMesh
{
private:
	unsigned int _vaoHandle;
	std::vector<unsigned int> _vboHandles;
	std::weak_ptr<IGraphicsContext> _graphicsContext;

public:
	AMesh();
	virtual ~AMesh() {}

	void init(const std::weak_ptr<IGraphicsContext>& context);
	void deinit();
	void draw();

	virtual int getIndicesCount() = 0;

protected:
	virtual void generateMesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<unsigned short>& indices) = 0;
};
