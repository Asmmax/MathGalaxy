#include "drawables/Sky.hpp"
#include "infrastruct/resources/AMesh.hpp"
#include "drawables/materials/SkyMaterial.hpp"
#include "infrastruct/DrawContext.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include <glm/gtx/transform.hpp>

Sky::Sky(const std::shared_ptr<AMesh>& mesh, const std::shared_ptr<Shader>& shader):
	_ambientColor(0.0f, 0.0f, 0.0f),
	_mesh(mesh),
	_material(std::make_shared<SkyMaterial>(shader)),
	_size(500.0f)
{
}

void Sky::setBaseColor(const glm::vec3& color)
{
	_material->setBaseColor(color);
}

void Sky::setBaseTexture(const std::shared_ptr<Texture>& texture)
{
	_material->setBaseTexture(texture);
}

void Sky::setAmbientColor(const glm::vec3& color)
{
	_ambientColor = color;
}

void Sky::setMesh(const std::shared_ptr<AMesh>& mesh)
{
	_mesh = mesh;

	if (_graphicsContext.expired()) {
		return;
	}

	if (_mesh) {
		_mesh->init(_graphicsContext);
	}
}

void Sky::init(const std::weak_ptr<IGraphicsContext>& context)
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

	if (_mesh) {
		_mesh->init(_graphicsContext);
	}

	if (_material) {
		_material->init(_graphicsContext);
	}
}

void Sky::deinit()
{
	auto sharedContext = _graphicsContext.lock();
	if (!sharedContext) {
		return;
	}
	sharedContext->makeCurrent();

	if (_mesh) {
		_mesh->deinit();
	}

	if (_material) {
		_material->deinit();
	}

	_graphicsContext.reset();
}

void Sky::predraw(DrawContext& context)
{
	context.add("AmbientColor", _ambientColor);
}

void Sky::draw(const DrawContext& context)
{
	if (!_mesh) {
		return;
	}

	DrawContext copyContext(context);

	auto viewMatrix = copyContext.getMat4x4("ViewMatrix");
	auto modelMatrix = glm::inverse(viewMatrix) * glm::scale(glm::vec3(_size));
	copyContext.add("ModelMatrix", modelMatrix);

	copyContext.add("Origin", glm::inverse(viewMatrix) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	_material->apply(copyContext);

	_mesh->draw();

	_material->clear();
}
