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
	std::vector<std::pair<std::string, Texture*>> _textures;

public:
	Object();

	DrawState& getState() { return _state; }
	const DrawState& getState() const { return _state; }

	void setMesh(Mesh* mesh);
	void setShader(Shader* shader);

	bool hasTexture(const std::string& name) const;
	void addTexture(const std::string& name, Texture* texture);
	void setTexture(const std::string& name, Texture* texture);
	void removeTexture(const std::string& name);

	void setMatrix(const glm::mat4& matrix);
	const glm::mat4& getMatrix() const { return _matrix; }

	void draw(DrawStatePool& statePool);
};
