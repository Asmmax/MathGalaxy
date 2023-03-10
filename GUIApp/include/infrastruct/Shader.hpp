#pragma once
#include <string>
#include <memory>
#include "glm/glm.hpp"

class IGraphicsContext;

class Shader
{
private:
	std::string _vertexShader;
	std::string _fragmentShader;
	unsigned int _vertexShaderHandle;
	unsigned int _fragmentShaderHandle;
	unsigned int _programHandle;
	std::weak_ptr<IGraphicsContext> _graphicsContext;

public:
	Shader();
	Shader(const std::string& vertexShader, const std::string& fragmentShader);

	void init(const std::weak_ptr<IGraphicsContext>& context);
	void deinit();

	void loadVertexShader(const std::string& fileName);
	void loadFragmentShader(const std::string& fileName);

	void setVertexShader(const std::string& text) { _vertexShader = text; }
	void setFragmentShader(const std::string& text) { _fragmentShader = text; }

	void use();

	void setUniform(const std::string& name, const glm::mat4& matrix);
	void setUniform(const std::string& name, const glm::mat3& matrix);
	void setUniform(const std::string& name, const glm::vec4& vector);
	void setUniform(const std::string& name, const glm::vec3& vector);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, int value);

private:
	void compileVertexShader();
	void compileFragmentShader();
	void link();
};
