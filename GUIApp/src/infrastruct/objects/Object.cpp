#include "infrastruct/objects/Object.hpp"
#include "infrastruct/resources/Mesh.hpp"
#include "infrastruct/StringId.hpp"
#include "infrastruct/resources/Shader.hpp"

Object::Object():
	_matrix(),
	_mesh(nullptr)
{
}

void Object::setMesh(Mesh* mesh)
{
	_mesh = mesh;
}

void Object::setMatrix(const glm::mat4& matrix)
{
	_matrix = matrix;
}

void Object::draw(Shader* shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
	auto mvMatrix = viewMatrix * _matrix;
	auto normalMatrix4x4 = glm::transpose(glm::inverse(mvMatrix));
	glm::mat3 normalMatrix(normalMatrix4x4);

	static StringId modelMatrixName = StringId("ModelMatrix");
	auto modelMatrixLocation = shader->getLocation(modelMatrixName);
	if (modelMatrixLocation != -1) {
		shader->setUniform(modelMatrixLocation, _matrix);
	}

	static StringId mvMatrixName = StringId("ModelViewMatrix");
	auto mvMatrixLocation = shader->getLocation(mvMatrixName);
	if (mvMatrixLocation != -1) {
		shader->setUniform(mvMatrixLocation, mvMatrix);
	}

	static StringId mvpMatrixName = StringId("MVP");
	auto mvpMatrixLocation = shader->getLocation(mvpMatrixName);
	if (mvpMatrixLocation != -1) {
		shader->setUniform(mvpMatrixLocation, projMatrix * mvMatrix);
	}

	static StringId normalMatrixName = StringId("NormalMatrix");
	auto normalMatrixLocation = shader->getLocation(normalMatrixName);
	if (normalMatrixLocation != -1) {
		shader->setUniform(normalMatrixLocation, normalMatrix);
	}

	if (_mesh) {
		_mesh->draw();
	}
}
