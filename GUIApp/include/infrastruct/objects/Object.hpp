#pragma once
#include "infrastruct/DrawState.hpp"
#include <memory>
#include <string>
#include <vector>
#include <glm/mat4x4.hpp>

class Shader;
class Mesh;
class Texture;

class Object
{
private:
	glm::mat4 _matrix;
	DrawState _state;
	Shader* _shader;
	Mesh* _mesh;
	std::vector<std::pair<StringId, Texture*>> _textures;

public:
	Object();

	DrawState& getState() { return _state; }
	const DrawState& getState() const { return _state; }

	void setMesh(Mesh* mesh);
	void setShader(Shader* shader);

	bool hasTexture(const StringId& name) const;
	void addTexture(const StringId& name, Texture* texture);
	void setTexture(const StringId& name, Texture* texture);
	void removeTexture(const StringId& name);

	void setMatrix(const glm::mat4& matrix);
	const glm::mat4& getMatrix() const { return _matrix; }

	void draw(DrawStatePool& statePool);
};
