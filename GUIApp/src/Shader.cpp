#include "Shader.hpp"
#include "gl/gl_core_4_3.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>

std::shared_ptr<Shader> Shader::defaultShader = std::make_shared<Shader>(
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

Shader::Shader():
	_vertexShaderHandle(0),
	_fragmentShaderHandle(0),
	_programHandle(0),
	_isInited(false)
{
}

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader):
	_vertexShaderHandle(0),
	_fragmentShaderHandle(0),
	_programHandle(0),
	_isInited(false)
{
	setVertexShader(vertexShader);
	setFragmentShader(fragmentShader);
}

void Shader::loadVertexShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (!file.is_open()) {
		fprintf(stderr, "Vertex shader file could not be open!\n");
		return;
	}

	_vertexShader.clear();
	_vertexShader.reserve(100);

	char c;
	while (!file.eof()) {
		file.get(c);
		_vertexShader.push_back(c);
	}

	file.close();
}

void Shader::loadFragmentShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	if (!file.is_open()) {
		fprintf(stderr, "Fragment shader file could not be open!");
		return;
	}

	_fragmentShader.clear();
	_fragmentShader.reserve(100);

	char c;
	while (!file.eof()) {
		file.get(c);
		_fragmentShader.push_back(c);
	}

	file.close();
}

void Shader::use()
{
	if (!_isInited) {
		init();
	}

	gl::UseProgram(_programHandle);
}

void Shader::setUniform(const std::string& name, const glm::mat4& matrix)
{
	GLuint location = gl::GetUniformLocation(_programHandle, name.c_str());
	if (location >= 0) {
		gl::UniformMatrix4fv(location, 1, gl::FALSE_, glm::value_ptr(matrix));
	}
}

void Shader::setUniform(const std::string& name, const glm::mat3& matrix)
{
	GLuint location = gl::GetUniformLocation(_programHandle, name.c_str());
	if (location >= 0) {
		gl::UniformMatrix3fv(location, 1, gl::FALSE_, glm::value_ptr(matrix));
	}
}

void Shader::setUniform(const std::string& name, const glm::vec4& vector)
{
	GLuint location = gl::GetUniformLocation(_programHandle, name.c_str());
	if (location >= 0) {
		gl::Uniform4fv(location, 1, glm::value_ptr(vector));
	}
}

void Shader::setUniform(const std::string& name, const glm::vec3& vector)
{
	GLuint location = gl::GetUniformLocation(_programHandle, name.c_str());
	if (location >= 0) {
		gl::Uniform3fv(location, 1, glm::value_ptr(vector));
	}
}

void Shader::setUniform(const std::string& name, int value)
{
	GLuint location = gl::GetUniformLocation(_programHandle, name.c_str());
	if (location >= 0) {
		gl::Uniform1iv(location, 1, &value);
	}
}

void Shader::init()
{
	compileVertexShader();
	compileFragmentShader();
	link();
	_isInited = true;
}

void Shader::compileVertexShader()
{
	if (_vertexShader.empty()) {
		fprintf(stderr, "Vertex shader is None.\n");
		return;
	}

	_vertexShaderHandle = gl::CreateShader(gl::VERTEX_SHADER);
	if (_vertexShaderHandle == 0) {
		fprintf(stderr, "Error creating vertex shader.\n");
		return;
	}

	const GLchar* shaderCode = _vertexShader.c_str();
	const GLchar* codeArray[] = { shaderCode };
	gl::ShaderSource(_vertexShaderHandle, 1, codeArray, NULL);

	gl::CompileShader(_vertexShaderHandle);

	GLint result;
	gl::GetShaderiv(_vertexShaderHandle, gl::COMPILE_STATUS, &result);
	if (result == gl::FALSE_) {
		fprintf(stderr, "Vertex shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(_vertexShaderHandle, gl::INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			GLchar* log = new char[logLen];
			GLsizei written;
			gl::GetShaderInfoLog(_vertexShaderHandle, logLen, &written, log);

			fprintf(stderr, "Shader log:\n%s", log);
			delete[] log;
		}
	}
}

void Shader::compileFragmentShader()
{
	if (_fragmentShader.empty()) {
		fprintf(stderr, "Fragment shader is None.\n");
		return;
	}

	_fragmentShaderHandle = gl::CreateShader(gl::FRAGMENT_SHADER);
	if (_fragmentShaderHandle == 0) {
		fprintf(stderr, "Error creating fragment shader.\n");
		return;
	}

	const GLchar* shaderCode = _fragmentShader.c_str();
	const GLchar* codeArray[] = { shaderCode };
	gl::ShaderSource(_fragmentShaderHandle, 1, codeArray, NULL);

	gl::CompileShader(_fragmentShaderHandle);

	GLint result;
	gl::GetShaderiv(_fragmentShaderHandle, gl::COMPILE_STATUS, &result);
	if (result == gl::FALSE_) {
		fprintf(stderr, "Fragment shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(_fragmentShaderHandle, gl::INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			GLchar* log = new char[logLen];
			GLsizei written;
			gl::GetShaderInfoLog(_fragmentShaderHandle, logLen, &written, log);

			fprintf(stderr, "Shader log:\n%s", log);
			delete[] log;
		}
	}
}

void Shader::link()
{
	_programHandle = gl::CreateProgram();
	if (_programHandle == 0) {
		fprintf(stderr, "Error creating shader program.\n");
		return;
	}

	if (_vertexShaderHandle != 0) {
		gl::AttachShader(_programHandle, _vertexShaderHandle);
	}

	if (_fragmentShaderHandle != 0) {
		gl::AttachShader(_programHandle, _fragmentShaderHandle);
	}

	gl::LinkProgram(_programHandle);

	GLint result;
	gl::GetShaderiv(_programHandle, gl::LINK_STATUS, &result);
	if (result == gl::FALSE_) {
		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		gl::GetShaderiv(_programHandle, gl::INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			GLchar* log = new char[logLen];
			GLsizei written;
			gl::GetShaderInfoLog(_programHandle, logLen, &written, log);

			fprintf(stderr, "Program log:\n%s", log);
			delete[] log;
		}
	}

	if (_vertexShaderHandle != 0) {
		gl::DetachShader(_programHandle, _vertexShaderHandle);
		gl::DeleteShader(_vertexShaderHandle);
		_vertexShaderHandle = 0;
	}

	if (_fragmentShaderHandle != 0) {
		gl::DetachShader(_programHandle, _fragmentShaderHandle);
		gl::DeleteShader(_fragmentShaderHandle);
		_fragmentShaderHandle = 0;
	}
}
