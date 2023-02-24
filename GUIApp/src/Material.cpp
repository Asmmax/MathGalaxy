#include "Material.hpp"
#include "Shader.hpp"

Material::Material():
	_shader(Shader::defaultShader),
	_mainColor(1.0f, 1.0f, 1.0f)
{
}

void Material::setShader(const std::shared_ptr<Shader>& shader)
{
	_shader = shader;
}

void Material::setMainColor(const glm::vec3& color)
{
	_mainColor = color;
}

void Material::apply(const DrawContext& context, const glm::mat4& modelMatrix)
{
	if (!_shader) {
		return;
	}

	_shader->use();

	glm::mat4 mvpMatrix = context.projectionMatrix * context.viewMatrix * modelMatrix;
	_shader->setUniform("ModelMatrix", modelMatrix);
	_shader->setUniform("ViewMatrix", context.viewMatrix);
	_shader->setUniform("ProjectionMatrix", context.projectionMatrix);
	_shader->setUniform("MVP", mvpMatrix);
	_shader->setUniform("MainColor", _mainColor);
}
