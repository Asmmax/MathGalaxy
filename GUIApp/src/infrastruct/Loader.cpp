#include "infrastruct/Loader.hpp"
#include "infrastruct/ILoaderImpl.hpp"
#include "infrastruct/resources/IMeshImpl.hpp"
#include "infrastruct/resources/ITextureImpl.hpp"
#include "infrastruct/resources/IShaderImpl.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include <assert.h>

Loader::Loader(ILoaderImpl* loaderImpl):
	_impl(loaderImpl),
	_context(nullptr)
{
}

Loader::~Loader()
{
	if (!_context) {
		return;
	}
	_context->makeCurrent();

	for (auto meshPtr : _meshes) {
		delete meshPtr;
	}

	for (auto texturePtr : _textures) {
		delete texturePtr;
	}

	for (auto shaderPtr : _shaders) {
		delete shaderPtr;
	}

	delete _impl;
}

void Loader::init(IGraphicsContext* context)
{
	_context = context;
}

Mesh* Loader::loadMesh(const MeshData& data)
{
	if (!_context) {
		return nullptr;
	}
	_context->makeCurrent();

	auto meshImpl = _impl->createMesh();
	if (!meshImpl) {
		return nullptr;
	}

	Mesh* newMesh = new Mesh(meshImpl);
	newMesh->init(data);
	_meshes.push_back(newMesh);
	return newMesh;
}

Texture* Loader::loadTexture(const TextureData& data)
{
	if (!_context) {
		return nullptr;
	}
	_context->makeCurrent();

	auto textureImpl = _impl->createTexture();
	if (!textureImpl) {
		return nullptr;
	}

	Texture* newTexture = new Texture(textureImpl);
	newTexture->init(data);
	_textures.push_back(newTexture);
	return newTexture;
}

Shader* Loader::loadShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	if (!_context) {
		return nullptr;
	}
	_context->makeCurrent();

	auto shaderImpl = _impl->createShader();
	if (!shaderImpl) {
		return nullptr;
	}

	Shader* newShader = new Shader(shaderImpl);
	newShader->init(vertexShader, fragmentShader);
	_shaders.push_back(newShader);
	return newShader;
}

void Loader::release(Mesh* mesh)
{
	if (!mesh) {
		return;
	}

	if (!_context) {
		return;
	}
	_context->makeCurrent();

	auto foundIt = std::find(_meshes.begin(), _meshes.end(), mesh);
	if (foundIt == _meshes.end()) {
		return;
	}

	delete mesh;
	_meshes.erase(foundIt);
}

void Loader::release(Texture* texture)
{
	if (!texture) {
		return;
	}

	if (!_context) {
		return;
	}
	_context->makeCurrent();

	auto foundIt = std::find(_textures.begin(), _textures.end(), texture);
	if (foundIt == _textures.end()) {
		return;
	}

	delete texture;
	_textures.erase(foundIt);
}

void Loader::release(Shader* shader)
{
	if (!shader) {
		return;
	}

	if (!_context) {
		return;
	}
	_context->makeCurrent();

	auto foundIt = std::find(_shaders.begin(), _shaders.end(), shader);
	if (foundIt == _shaders.end()) {
		return;
	}

	delete shader;
	_shaders.erase(foundIt);
}
