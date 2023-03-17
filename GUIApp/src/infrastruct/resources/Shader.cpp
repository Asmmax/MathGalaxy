#include "infrastruct/resources/Shader.hpp"
#include "infrastruct/resources/IShaderImpl.hpp"

Shader::Shader(IShaderImpl* shaderImpl):
	_impl(shaderImpl)
{
}

Shader::~Shader()
{
	_impl->terminate();
	delete _impl;
}

void Shader::init(const std::string& vertexShader, const std::string& fragmentShader)
{
	_impl->compileVertexShader(vertexShader);
	_impl->compileFragmentShader(fragmentShader);
	_impl->link();
}

void Shader::use()
{
	_impl->use();
}

void Shader::clear()
{
	_impl->clear();
}

void Shader::setUniform(const std::string& name, const glm::mat4& matrix)
{
	_impl->setUniform(name, matrix);
}

void Shader::setUniform(const std::string& name, const glm::mat3& matrix)
{
	_impl->setUniform(name, matrix);
}

void Shader::setUniform(const std::string& name, const glm::vec4& vector)
{
	_impl->setUniform(name, vector);
}

void Shader::setUniform(const std::string& name, const glm::vec3& vector)
{
	_impl->setUniform(name, vector);
}

void Shader::setUniform(const std::string& name, float value)
{
	_impl->setUniform(name, value);
}

void Shader::setUniform(const std::string& name, int value)
{
	_impl->setUniform(name, value);
}
