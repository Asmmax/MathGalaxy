#pragma once
#include "infrastruct/resources/IShaderImpl.hpp"

class GLShaderImpl : public IShaderImpl
{
private:
	unsigned int _vertexShaderHandle;
	unsigned int _fragmentShaderHandle;
	unsigned int _programHandle;

public:
	GLShaderImpl();

	void compileVertexShader(const std::string& shader) override;
	void compileFragmentShader(const std::string& shader) override;
	void link() override;

	void terminate() override;

	void use() override;
	void clear() override;

	void setUniform(unsigned int location, const glm::mat4& matrix) override;
	void setUniform(unsigned int location, const glm::mat3& matrix) override;
	void setUniform(unsigned int location, const glm::vec4& vector) override;
	void setUniform(unsigned int location, const glm::vec3& vector) override;
	void setUniform(unsigned int location, float value) override;
	void setUniform(unsigned int location, int value) override;

	unsigned int getLocation(const StringId& name) const override;
};
