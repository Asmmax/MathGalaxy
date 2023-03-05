#include "materials/ColoredMaterial.hpp"
#include "Shader.hpp"

std::shared_ptr<Shader> ColoredMaterial::defaultShader = std::make_shared<Shader>(
	"#version 430\n"
	"layout (location = 0) in vec3 Position;\n"
	"uniform mat4 MVP;\n"
	"void main()\n"
	"{\n"
	"    gl_Position = MVP * vec4(Position, 1.0f);\n"
	"}\n"
	,
	"#version 430\n"
	"out vec4 FragColor;\n"
	"uniform vec3 MainColor;\n"
	"void main()\n"
	"{\n"
	"    FragColor = vec4(MainColor,1.0);\n"
	"}\n"
	);

ColoredMaterial::ColoredMaterial() :
	AMaterial(ColoredMaterial::defaultShader),
	_mainColor(1.0f, 1.0f, 1.0f)
{
}

void ColoredMaterial::setMainColor(const glm::vec3& color)
{
	_mainColor = color;
}

void ColoredMaterial::applyImpl()
{
	getShader()->setUniform("MainColor", _mainColor);
}
