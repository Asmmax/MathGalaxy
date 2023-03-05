#include "materials/StarMaterial.hpp"
#include "Shader.hpp"

StarMaterial::StarMaterial(const std::shared_ptr<Shader>& shader):
	AMaterial(shader),
	_baseColor(1.0f,1.0f,1.0f),
	_boundColor(1.0f, 1.0f, 1.0f),
	_spaceColor(0.0f, 0.0f, 0.0f)
{
}

void StarMaterial::setBaseColor(const glm::vec3& color)
{
	_baseColor = color;
}

void StarMaterial::setBoundColor(const glm::vec3& color)
{
	_boundColor = color;
}

void StarMaterial::setSpaceColor(const glm::vec3& color)
{
	_spaceColor = color;
}

void StarMaterial::applyImpl()
{
	getShader()->setUniform("Star.BaseColor", _baseColor);
	getShader()->setUniform("Star.BoundColor", _boundColor);
	getShader()->setUniform("Star.SpaceColor", _spaceColor);
}
