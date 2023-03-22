#pragma once
#include <glm/mat4x4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <string>

class IShaderImpl
{
public:
	virtual ~IShaderImpl() {}

	virtual void compileVertexShader(const std::string& shader) = 0;
	virtual void compileFragmentShader(const std::string& shader) = 0;
	virtual void link() = 0;

	virtual void terminate() = 0;

	virtual void use() = 0;
	virtual void clear() = 0;

	virtual void setUniform(const std::string& name, const glm::mat4& matrix) = 0;
	virtual void setUniform(const std::string& name, const glm::mat3& matrix) = 0;
	virtual void setUniform(const std::string& name, const glm::vec4& vector) = 0;
	virtual void setUniform(const std::string& name, const glm::vec3& vector) = 0;
	virtual void setUniform(const std::string& name, float value) = 0;
	virtual void setUniform(const std::string& name, int value) = 0;
};