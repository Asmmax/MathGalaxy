#pragma once
#include "infrastruct/DrawState.hpp"
#include <glm/mat4x4.hpp>

class Mesh;
class Shader;

class Object
{
private:
	glm::mat4 _matrix;
	Mesh* _mesh;

public:
	Object();

	void setMesh(Mesh* mesh);

	void setMatrix(const glm::mat4& matrix);
	const glm::mat4& getMatrix() const { return _matrix; }

	void draw(Shader* shader, const glm::mat4& viewMatrix, const glm::mat4& projMatrix);
};
