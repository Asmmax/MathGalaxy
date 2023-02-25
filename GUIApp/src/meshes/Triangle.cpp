#include "meshes/Triangle.hpp"
#include "gl/gl_core_4_3.hpp"

Triangle::Triangle(float size):
    _size(size)
{
}

int Triangle::getIndicesCount()
{
    return 3;
}

void Triangle::generateMesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<unsigned short>& indices)
{
    vertices.reserve(3);
    vertices.emplace_back(0, _size / 2, 0);
    vertices.emplace_back(_size / 2, -_size / 2, 0);
    vertices.emplace_back(-_size / 2, -_size / 2, 0);

    normals.reserve(3);
    normals.emplace_back(0, 0, 1);
    normals.emplace_back(0, 0, 1);
    normals.emplace_back(0, 0, 1);

    indices.reserve(3);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
}
