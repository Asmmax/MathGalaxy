#pragma once
#include "infrastruct/resources/IMeshImpl.hpp"
#include "infrastruct/PoolAllocator.hpp"
#include <vector>

class GLMeshImpl : public IMeshImpl
{
private:
	unsigned int _vaoHandle;
	std::vector<unsigned int> _vboHandles;
	PoolAllocator<GLMeshImpl>* _allocator;

public:
	GLMeshImpl(PoolAllocator<GLMeshImpl>* allocator);

	void init() override;
	void terminate() override;
	void free() override;

	void draw(size_t indicesCount) override;

	void updateData(const MeshData& data) override;
};
