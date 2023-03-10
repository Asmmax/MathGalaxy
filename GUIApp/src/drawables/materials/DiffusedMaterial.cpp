#include "drawables/materials/DiffusedMaterial.hpp"
#include "infrastruct/resources/Shader.hpp"

DiffusedMaterial::DiffusedMaterial(const std::shared_ptr<Shader>& shader):
	AMaterial(shader),
	_diffuseColor(1.0f, 1.0f, 1.0f),
	_ambientFactor(0.2f),
	_diffuseFactor(0.8f)
{
}

void DiffusedMaterial::setDiffuseColor(const glm::vec3& color)
{
	_diffuseColor = color;
}

void DiffusedMaterial::setAmbientFactor(float factor)
{
	_ambientFactor = factor;
}

void DiffusedMaterial::setDiffuseFactor(float factor)
{
	_diffuseFactor = factor;
}

void DiffusedMaterial::applyImpl()
{
	getShader()->setUniform("Material.DiffuseColor", _diffuseColor);
	getShader()->setUniform("Material.AmbientFactor", _ambientFactor);
	getShader()->setUniform("Material.DiffuseFactor", _diffuseFactor);
}
