#include "infrastruct/resources/AMesh.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include "gl/gl_core_4_3.hpp"

AMesh::AMesh():
	_vaoHandle(0)
{
}

void AMesh::init(const std::weak_ptr<IGraphicsContext>& context)
{
	auto sharedContext = context.lock();
	if (_graphicsContext.lock() == sharedContext) {
		return;
	}

	deinit();
	_graphicsContext = context;

	if (!sharedContext) {
		return;
	}
	sharedContext->makeCurrent();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> indices;
	generateMesh(vertices, normals, indices);

	_vboHandles.resize(3);
	gl::GenBuffers(3, &_vboHandles[0]);
	GLuint posBufHandle = _vboHandles[0];
	GLuint normBufHandle = _vboHandles[1];
	GLuint elemBufHandle = _vboHandles[2];

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, elemBufHandle);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(short), indices.data(), gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, posBufHandle);
	gl::BufferData(gl::ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, normBufHandle);
	gl::BufferData(gl::ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), gl::STATIC_DRAW);

	gl::GenVertexArrays(1, &_vaoHandle);
	gl::BindVertexArray(_vaoHandle);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, elemBufHandle);

	gl::EnableVertexAttribArray(0);
	gl::EnableVertexAttribArray(1);

	gl::BindBuffer(gl::ARRAY_BUFFER, posBufHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, NULL);

	gl::BindBuffer(gl::ARRAY_BUFFER, normBufHandle);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, gl::FALSE_, 0, NULL);

	gl::BindVertexArray(0);
}

void AMesh::deinit()
{
	auto sharedContext = _graphicsContext.lock();
	if (!sharedContext) {
		return;
	}
	sharedContext->makeCurrent();

	gl::DeleteVertexArrays(1, &_vaoHandle);
	_vaoHandle = 0;

	gl::DeleteBuffers(static_cast<GLsizei>(_vboHandles.size()), &_vboHandles[0]);
	_vboHandles.clear();

	_graphicsContext.reset();
}

void AMesh::draw()
{
	gl::BindVertexArray(_vaoHandle);

	const int indicesCount = getIndicesCount();
	gl::DrawElements(gl::TRIANGLES, indicesCount, gl::UNSIGNED_SHORT, 0);
}
