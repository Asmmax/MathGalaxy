#pragma once
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

	void setUniform(const std::string& name, const glm::mat4& matrix);
	void setUniform(const std::string& name, const glm::mat3& matrix);
	void setUniform(const std::string& name, const glm::vec4& vector);
	void setUniform(const std::string& name, const glm::vec3& vector);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, int value);
};
