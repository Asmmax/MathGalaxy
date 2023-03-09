#include "Sky.hpp"
#include "AMesh.hpp"
#include "materials/SkyMaterial.hpp"
#include "DrawContext.hpp"
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
}

void Sky::init()
{
	if (_mesh) {
		_mesh->init();
	}
}

void Sky::predraw(DrawContext& context)
{
	context.add("AmbientColor", _ambientColor);
}

void Sky::draw(DrawContext& context)
{
	if (!_mesh) {
		return;
	}

	auto viewMatrix = context.getMat4x4("ViewMatrix");
	auto modelMatrix = glm::inverse(viewMatrix) * glm::scale(glm::vec3(_size));
	context.add("ModelMatrix", modelMatrix);

	context.add("Origin", glm::inverse(viewMatrix) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	_material->apply(context);

	_mesh->draw();

	_material->clear();
}
