#include "drawables/AMaterial.hpp"
#include "infrastruct/Shader.hpp"
#include "infrastruct/DrawContext.hpp"
#include "drawables/Texture.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include "gl/gl_core_4_3.hpp"
#include <assert.h>

AMaterial::AMaterial(const std::shared_ptr<Shader>& shader) :
	_shader(shader)
{
}

void AMaterial::setShader(const std::shared_ptr<Shader>& shader)
{
	_shader = shader;

	if (_graphicsContext.expired()) {
		return;
	}

	if (_shader) {
		_shader->init(_graphicsContext);
	}
}

void AMaterial::init(const std::weak_ptr<IGraphicsContext>& context)
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

	if (_shader) {
		_shader->init(_graphicsContext);
	}

	for (auto& texture : _textures) {
		texture.second->init(_graphicsContext);
	}
}

void AMaterial::deinit()
{
	auto sharedContext = _graphicsContext.lock();
	if (!sharedContext) {
		return;
	}
	sharedContext->makeCurrent();

	if (_shader) {
		_shader->deinit();
	}

	for (auto& texture : _textures) {
		texture.second->deinit();
	}

	_graphicsContext.reset();
}

void AMaterial::apply(const DrawContext& context)
{
	if (!_shader) {
		return;
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

	if (_graphicsContext.expired()) {
		return;
	}

	_textures[name]->init(_graphicsContext);
}

void AMaterial::removeTexture(const std::string& name)
{
	assert(_textures.find(name) != _textures.end());
	_textures[name]->clear();
	_textures.erase(name);
}
