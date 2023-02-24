#include "AMesh.hpp"
#include "gl/gl_core_4_3.hpp"

AMesh::AMesh():
	_vaoHandle(0)
{
}

void AMesh::init()
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned short> indices;
	generateMesh(vertices, indices);

	GLuint vboHandles[2];
	gl::GenBuffers(2, &vboHandles[0]);
	GLuint posBufHandle = vboHandles[0];
	GLuint elemBufHandle = vboHandles[1];

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, elemBufHandle);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(short), indices.data(), gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, posBufHandle);
	gl::BufferData(gl::ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), gl::STATIC_DRAW);

	gl::GenVertexArrays(1, &_vaoHandle);
	gl::BindVertexArray(_vaoHandle);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, elemBufHandle);

	gl::EnableVertexAttribArray(0);

	gl::BindBuffer(gl::ARRAY_BUFFER, posBufHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);

	gl::BindVertexArray(0);
}

void AMesh::draw()
{
	gl::BindVertexArray(_vaoHandle);

	const int indicesCount = getIndicesCount();
	gl::DrawElements(gl::TRIANGLES, indicesCount, gl::UNSIGNED_SHORT, 0);
}
