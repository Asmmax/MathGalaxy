#include "infrastruct/resources/Mesh.hpp"
#include "infrastruct/resources/IMeshImpl.hpp"
#include "infrastruct/resources/MeshData.hpp"

Mesh::Mesh(IMeshImpl* meshImpl):
	_impl(meshImpl),
	_indicesCount(0)
{
}

Mesh::~Mesh()
{
	_impl->terminate();
	delete _impl;
}

void Mesh::init(const MeshData& data)
{
	_impl->init();
	updateData(data);
}

void Mesh::updateData(const MeshData& data)
{
	_impl->updateData(data);
	_indicesCount = data.indices.size();

	for (auto& point : data.positions) {
		_bounds.addPoint(point.x, point.y, point.z);
	}
}

void Mesh::draw()
{
	_impl->draw(_indicesCount);
}
