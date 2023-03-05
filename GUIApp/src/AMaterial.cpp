#include "AMaterial.hpp"
#include "Shader.hpp"
#include "DrawContext.hpp"
#include "Texture.hpp"
#include "gl/gl_core_4_3.hpp"
#include <assert.h>

AMaterial::AMaterial(const std::shared_ptr<Shader>& shader) :
	_shader(shader),
	_isInited(false)
{
}

void AMaterial::setShader(const std::shared_ptr<Shader>& shader)
{
	_shader = shader;
}

void AMaterial::apply(const DrawContext& context)
{
	if (!_shader) {
		return;
	}

	if (!_isInited) {
		init();
		_isInited = true;
	}

	_shader->use();

	context.apply(*_shader);

	auto& modelMatrix = context.getMat4x4("ModelMatrix");
	auto& viewMatrix = context.getMat4x4("ViewMatrix");
	auto& projMatrix = context.getMat4x4("ProjectionMatrix");
	auto modelViewMatrix = viewMatrix * modelMatrix;
	auto normalMatrix4x4 = glm::transpose(glm::inverse(modelViewMatrix));
	glm::mat3 normalMatrix(normalMatrix4x4);

	_shader->setUniform("ModelViewMatrix", modelViewMatrix);
	_shader->setUniform("MVP", projMatrix * modelViewMatrix);
	_shader->setUniform("NormalMatrix", normalMatrix);

	int textureUnit = 0;
	for (auto& texture : _textures) {
		texture.second->apply(textureUnit);
		_shader->setUniform(texture.first, textureUnit);
		textureUnit++;
	}

	applyImpl();
}

void AMaterial::clear()
{
	gl::UseProgram(0);
}

void AMaterial::addTexture(const std::string& name, const std::shared_ptr<Texture>& texture)
{
	if (!texture) {
		return;
	}
	_textures[name] = texture;
	_isInited = false;
}

void AMaterial::removeTexture(const std::string& name)
{
	assert(_textures.find(name) != _textures.end());
	_textures[name]->clear();
	_textures.erase(name);
}

void AMaterial::init()
{
	for (auto& texture : _textures) {
		texture.second->init();
	}
}
