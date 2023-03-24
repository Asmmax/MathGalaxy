#pragma once
#include "infrastruct/resources/IShaderImpl.hpp"
#include <string>
#include <vector>
#include <unordered_map>

class GLShaderImpl : public IShaderImpl
{
private:
	unsigned int _vertexShaderHandle;
	unsigned int _fragmentShaderHandle;
	unsigned int _programHandle;

	mutable std::vector<StringId> _names;
	mutable std::vector<unsigned int> _locations;

public:
	GLShaderImpl();

	void compileVertexShader(const std::string& shader) override;
	void compileFragmentShader(const std::string& shader) override;
	void link() override;

	void terminate() override;

	void use() override;
	void clear() override;

	void setUniform(const StringId& name, const glm::mat4& matrix) override;
	void setUniform(const StringId& name, const glm::mat3& matrix) override;
	void setUniform(const StringId& name, const glm::vec4& vector) override;
	void setUniform(const StringId& name, const glm::vec3& vector) override;
	void setUniform(const StringId& name, float value) override;
	void setUniform(const StringId& name, int value) override;

	unsigned int getLocation(const StringId& name) const;
};
