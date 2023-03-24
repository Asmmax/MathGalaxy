#pragma once
#include "infrastruct/StringId.hpp"
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <string>

class IShaderImpl;

class Shader
{
private:
	IShaderImpl* _impl;

public:
	Shader(IShaderImpl* shaderImpl);
	~Shader();

	void init(const std::string& vertexShader, const std::string& fragmentShader);

	void use();
	void clear();

	void setUniform(const StringId& name, const glm::mat4& matrix);
	void setUniform(const StringId& name, const glm::mat3& matrix);
	void setUniform(const StringId& name, const glm::vec4& vector);
	void setUniform(const StringId& name, const glm::vec3& vector);
	void setUniform(const StringId& name, float value);
	void setUniform(const StringId& name, int value);
};
