#include "drawables/MeshNode.hpp"
#include "Material.hpp"
#include "Transform.hpp"
#include "AMesh.hpp"
#include "gl/gl_core_4_3.hpp"

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

void MeshNode::draw(const DrawContext& context)
{
	gl::UseProgram(0);

	if (_material) {
		_material->apply(context, getTransform()->getGlobalMatrix());
	}

	if (_mesh) {
		_mesh->draw();
	}
}
