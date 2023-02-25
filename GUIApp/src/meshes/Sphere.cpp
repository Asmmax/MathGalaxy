#include "meshes/Sphere.hpp"
#include "gl/gl_core_4_3.hpp"
#include "glm/gtx/normal.hpp"

const float pi = 3.1415926536f;

Sphere::Sphere(float radius, unsigned int segCount):
	_radius(radius),
	_segCount(segCount)
{
}

int Sphere::getIndicesCount()
{
	const int V = _segCount + 1;
	const int G = _segCount * 2 + 1;
	const int indicesCount = 6 * (V - 1) * (G - 1);
	return indicesCount;
}

void Sphere::generateMesh(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<unsigned short>& indices)
{
	createGeosphere(-pi / 2, pi / 2, _segCount, _radius, vertices, indices);

	normals.resize(vertices.size());

	for (size_t i = 0; i < indices.size(); i+=3) {
		const glm::vec3& p1 = vertices[indices[i + 0]];
		const glm::vec3& p2 = vertices[indices[i + 1]];
		const glm::vec3& p3 = vertices[indices[i + 2]];

		glm::vec3 normal = glm::triangleNormal(p1, p2, p3);
		normals[indices[i + 0]] += normal;
		normals[indices[i + 1]] += normal;
		normals[indices[i + 2]] += normal;
	}

	for (auto& normal: normals) {
		normal = glm::normalize(normal);
	}

}

void Sphere::createGeosphere(float fStart, float fEnd, int nSegs, float radius, std::vector<glm::vec3>& vertices, std::vector<unsigned short>& indices)
{
	int V = nSegs + 1;
	int G = nSegs * 2 + 1;
	vertices.resize(V * G);
	float theta, phi;
	int cnt = 0;
	for (int i = 0; i < V; i++) {
		phi = fStart + (fEnd - fStart) * i / (V - 1);
		for (int j = 0; j < G; j++) {
			theta = 2 * pi * j / (G - 1);
			vertices[cnt] = radius * glm::vec3(cos(phi) * cos(theta),
				sin(phi),
				cos(phi) * sin(theta));
			cnt++;
		};
	};
	indices.resize(6 * (V - 1) * (G - 1));
#define SET(x,y) ((x)*(G)+(y))
	for (int i = 0; i < V - 1; i++) {
		for (int j = 0; j < G - 1; j++) {
			indices[i * (G - 1) * 6 + j * 6 + 0] = SET(i + 0, j + 0);
			indices[i * (G - 1) * 6 + j * 6 + 2] = SET(i + 1, j + 1);
			indices[i * (G - 1) * 6 + j * 6 + 1] = SET(i + 1, j + 0);
			indices[i * (G - 1) * 6 + j * 6 + 3] = SET(i + 0, j + 0);
			indices[i * (G - 1) * 6 + j * 6 + 5] = SET(i + 0, j + 1);
			indices[i * (G - 1) * 6 + j * 6 + 4] = SET(i + 1, j + 1);
		};
	};
#undef SET
}
