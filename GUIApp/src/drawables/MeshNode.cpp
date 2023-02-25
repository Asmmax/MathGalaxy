#include "drawables/MeshNode.hpp"
#include "Material.hpp"
#include "Transform.hpp"
#include "AMesh.hpp"
#include "DrawContext.hpp"

void MeshNode::setMesh(const std::shared_ptr<AMesh>& mesh)
{
	_mesh = mesh;
}

void MeshNode::setMaterial(const std::shared_ptr<Material>& material)
{
	_material = material;
}

void MeshNode::init()
{
	if (_mesh) {
		_mesh->init();
	}
}

void MeshNode::predraw(DrawContext& /*context*/)
{
}

void MeshNode::draw(DrawContext& context)
{
	if (_material) {
		context.add("ModelMatrix", getTransform()->getGlobalMatrix());
		_material->apply(context);
	}

	if (_mesh) {
		_mesh->draw();
	}

	if (_material) {
		_material->clear();
	}
}
