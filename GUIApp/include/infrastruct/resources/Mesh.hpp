#pragma once

class IMeshImpl;
struct MeshData;

class Mesh
{
private:
	IMeshImpl* _impl;
	size_t _indicesCount;

public:
	Mesh(IMeshImpl* meshImpl);
	~Mesh();

	void init(const MeshData& data);
	void updateData(const MeshData& data);
	void draw();
};
