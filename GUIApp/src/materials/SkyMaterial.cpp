#include "materials/SkyMaterial.hpp"
#include "Shader.hpp"

SkyMaterial::SkyMaterial(const std::shared_ptr<Shader>& shader) :
	AMaterial(shader),
	_baseColor(0.0f, 0.0f, 0.0f)
{
}

void SkyMaterial::setBaseColor(const glm::vec3& color)
{
	_baseColor = color;
}

void SkyMaterial::setBaseTexture(const std::shared_ptr<Texture>& texture)
{
	addTexture("skyMap", texture);
}

void SkyMaterial::applyImpl()
{
	getShader()->setUniform("BaseColor", _baseColor);
}
