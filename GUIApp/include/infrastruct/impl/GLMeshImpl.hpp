#pragma once
#include "infrastruct/resources/IMeshImpl.hpp"
#include <vector>

class GLMeshImpl : public IMeshImpl
{
private:
	unsigned int _vaoHandle;
	std::vector<unsigned int> _vboHandles;
public:
	GLMeshImpl();

	void init() override;
	void terminate() override;

	void draw(size_t indicesCount) override;

	void updateData(const MeshData& data) override;
};
