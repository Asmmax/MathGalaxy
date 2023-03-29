#include "infrastruct/objects/Batch.hpp"
#include "infrastruct/objects/Object.hpp"
#include "infrastruct/resources/Shader.hpp"
#include "infrastruct/resources/Texture.hpp"

Batch::Batch() :
	_shader(nullptr)
{
}

void Batch::setShader(Shader* shader)
{
	_shader = shader;
}

bool Batch::hasTexture(const StringId& name) const
{
	auto&& it = std::find_if(_textures.begin(), _textures.end(), [name](auto& texturePair) {
		return texturePair.first == name;
		});

	return it != _textures.end();
}

void Batch::addTexture(const StringId& name, Texture* texture)
{
	if (!texture) {
		return;
	}

	assert(!hasTexture(name));

	_textures.emplace_back(name, texture);
}

void Batch::setTexture(const StringId& name, Texture* texture)
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

void Batch::removeTexture(const StringId& name)
{
	assert(hasTexture(name));
	auto&& it = std::find_if(_textures.begin(), _textures.end(), [name](auto& texturePair) {
		return texturePair.first == name;
		});
	_textures.erase(it);
}

Object* Batch::createObject()
{
	Object* newObject = new Object();
	_objects.push_back(newObject);
	return newObject;
}

void Batch::draw(DrawStatePoolDef& statePool)
{
	auto& state = statePool.get();

	_shader->use();

	state.apply(*_shader);

	int textureUnit = 0;
	for (auto& texture : _textures) {
		auto location = _shader->getLocation(texture.first);
		if (location == -1) {
			continue;
		}

		texture.second->apply(textureUnit);
		_shader->setUniform(location, textureUnit);
		textureUnit++;
	}

	_state.apply(*_shader);

	static StringId viewMatrixName = StringId("ViewMatrix");
	auto& viewMatrix = state.get<glm::mat4>(viewMatrixName);

	static StringId projMatrixName = StringId("ProjectionMatrix");
	auto& projMatrix = state.get<glm::mat4>(projMatrixName);

	for (auto& object : _objects)
	{
		object->draw(_shader, viewMatrix, projMatrix);
	}

	_shader->clear();
}
