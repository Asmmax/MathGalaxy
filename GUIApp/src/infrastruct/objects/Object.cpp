#include "infrastruct/objects/Object.hpp"
#include "infrastruct/resources/Shader.hpp"
#include "infrastruct/resources/Texture.hpp"
#include "infrastruct/resources/Mesh.hpp"
#include "infrastruct/DrawState.hpp"

Object::Object():
	_matrix(),
	_shader(nullptr),
	_mesh(nullptr)
{
}

void Object::setMesh(Mesh* mesh)
{
	_mesh = mesh;
}

void Object::setShader(Shader* shader)
{
	_shader = shader;
}

bool Object::hasTexture(const std::string& name) const
{
	auto&& it = std::find_if(_textures.begin(), _textures.end(), [name](auto& texturePair) {
		return texturePair.first == name;
		});

	return it != _textures.end();
}

void Object::addTexture(const std::string& name, Texture* texture)
{
	if (!texture) {
		return;
	}

	assert(!hasTexture(name));

	_textures.emplace_back(name, texture);
}

void Object::setTexture(const std::string& name, Texture* texture)
{
	if (!texture) {
		return;
	}

	assert(hasTexture(name));
	auto&& it = std::find_if(_textures.begin(), _textures.end(), [name](auto& texturePair) {
		return texturePair.first == name;
		});

	it->second = texture;
}

void Object::removeTexture(const std::string& name)
{
	assert(hasTexture(name));
	auto&& it = std::find_if(_textures.begin(), _textures.end(), [name](auto& texturePair) {
		return texturePair.first == name;
		});
	_textures.erase(it);
}

void Object::setMatrix(const glm::mat4& matrix)
{
	_matrix = matrix;
}

void Object::draw(DrawStatePool& statePool)
{
	auto& currentState = statePool.get();

	_shader->use();

	currentState.apply(*_shader);

	int textureUnit = 0;
	for (auto& texture : _textures) {
		texture.second->apply(textureUnit);
		_shader->setUniform(texture.first, textureUnit);
		textureUnit++;
	}

	_state.apply(*_shader);

	if (_mesh) {
		_mesh->draw();
	}

	_shader->clear();
}
