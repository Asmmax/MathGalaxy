#include "AMaterial.hpp"
#include "Shader.hpp"
#include "DrawContext.hpp"
#include "gl/gl_core_4_3.hpp"

AMaterial::AMaterial(const std::shared_ptr<Shader>& shader):
	_shader(shader)
{
}

void AMaterial::setShader(const std::shared_ptr<Shader>& shader)
{
	_shader = shader;
}

void AMaterial::apply(const DrawContext& context)
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

	applyImpl();
}

void AMaterial::clear()
{
	gl::UseProgram(0);
}
