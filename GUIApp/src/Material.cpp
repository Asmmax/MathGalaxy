#include "Material.hpp"
#include "Shader.hpp"
#include "DrawContext.hpp"
#include "gl/gl_core_4_3.hpp"

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

void Material::apply(const DrawContext& context)
{
	if (!_shader) {
		return;
	}

	_shader->use();

	context.apply(*_shader);

	auto& modelMatrix = context.getMat4x4("ModelMatrix");
	auto& viewMatrix = context.getMat4x4("ViewMatrix");
	auto& projMatrix = context.getMat4x4("ProjectionMatrix");
	auto modelViewMatrix = viewMatrix * modelMatrix;
	auto normalMatrix4x4 = glm::transpose(glm::inverse(modelViewMatrix));
	glm::mat3 normalMatrix(normalMatrix4x4);

	_shader->setUniform("ModelViewMatrix", modelViewMatrix);
	_shader->setUniform("MVP", projMatrix * modelViewMatrix);
	_shader->setUniform("NormalMatrix", normalMatrix);

	_shader->setUniform("MainColor", _mainColor);
}

void Material::clear()
{
	gl::UseProgram(0);
}
