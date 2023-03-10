#include "drawables/nodes/MeshNode.hpp"
#include "drawables/AMaterial.hpp"
#include "drawables/Transform.hpp"
#include "infrastruct/resources/AMesh.hpp"
#include "infrastruct/DrawContext.hpp"
#include "infrastruct/IGraphicsContext.hpp"

void MeshNode::setMesh(const std::shared_ptr<AMesh>& mesh)
{
	_mesh = mesh;

	if (_graphicsContext.expired()) {
		return;
	}

	if (_mesh) {
		_mesh->init(_graphicsContext);
	}
}

void MeshNode::setMaterial(const std::shared_ptr<AMaterial>& material)
{
	_material = material;

	if (_graphicsContext.expired()) {
		return;
	}

	if (_material) {
		_material->init(_graphicsContext);
	}
}

void MeshNode::init(const std::weak_ptr<IGraphicsContext>& context)
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

void MeshNode::deinit()
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

void MeshNode::predraw(DrawContext& /*context*/)
{
}

void MeshNode::draw(const DrawContext& context)
{
	DrawContext copyContext(context);
	if (_material) {
		copyContext.add("ModelMatrix", getTransform()->getGlobalMatrix());
		_material->apply(copyContext);
	}

	if (_mesh) {
		_mesh->draw();
	}

	if (_material) {
		_material->clear();
	}
}
