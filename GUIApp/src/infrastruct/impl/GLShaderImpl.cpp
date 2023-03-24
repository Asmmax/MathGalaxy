#include "infrastruct/impl/GLShaderImpl.hpp"
#include "infrastruct/DrawState.hpp"
#include "gl/gl_core_4_3.hpp"
#include "glm/gtc/type_ptr.hpp"

#undef DrawState

GLShaderImpl::GLShaderImpl():
	_vertexShaderHandle(0),
	_fragmentShaderHandle(0),
	_programHandle(0)
{
}

void GLShaderImpl::compileVertexShader(const std::string& shader)
{
	if (shader.empty()) {
		fprintf(stderr, "Vertex shader is None.\n");
		return;
	}

	_vertexShaderHandle = gl::CreateShader(gl::VERTEX_SHADER);
	if (_vertexShaderHandle == 0) {
		fprintf(stderr, "Error creating vertex shader.\n");
		return;
	}

	const GLchar* shaderCode = shader.c_str();
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

void GLShaderImpl::compileFragmentShader(const std::string& shader)
{
	if (shader.empty()) {
		fprintf(stderr, "Fragment shader is None.\n");
		return;
	}

	_fragmentShaderHandle = gl::CreateShader(gl::FRAGMENT_SHADER);
	if (_fragmentShaderHandle == 0) {
		fprintf(stderr, "Error creating fragment shader.\n");
		return;
	}

	const GLchar* shaderCode = shader.c_str();
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

void GLShaderImpl::link()
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

void GLShaderImpl::terminate()
{
	gl::DeleteProgram(_programHandle);
	_programHandle = 0;
}

void GLShaderImpl::use()
{
	gl::UseProgram(_programHandle);
}

void GLShaderImpl::clear()
{
	gl::UseProgram(0);
}

void GLShaderImpl::setUniform(const StringId& name, const glm::mat4& matrix)
{
	auto location = getLocation(name);
	if (location == -1) {
		return;
	}
	gl::UniformMatrix4fv(location, 1, gl::FALSE_, glm::value_ptr(matrix));
}

void GLShaderImpl::setUniform(const StringId& name, const glm::mat3& matrix)
{
	auto location = getLocation(name);
	if (location == -1) {
		return;
	}
	gl::UniformMatrix3fv(location, 1, gl::FALSE_, glm::value_ptr(matrix));
}

void GLShaderImpl::setUniform(const StringId& name, const glm::vec4& vector)
{
	auto location = getLocation(name);
	if (location == -1) {
		return;
	}
	gl::Uniform4fv(location, 1, glm::value_ptr(vector));
}

void GLShaderImpl::setUniform(const StringId& name, const glm::vec3& vector)
{
	auto location = getLocation(name);
	if (location == -1) {
		return;
	}
	gl::Uniform3fv(location, 1, glm::value_ptr(vector));
}

void GLShaderImpl::setUniform(const StringId& name, float value)
{
	auto location = getLocation(name);
	if (location == -1) {
		return;
	}
	gl::Uniform1f(location, value);
}

void GLShaderImpl::setUniform(const StringId& name, int value)
{
	auto location = getLocation(name);
	if (location == -1) {
		return;
	}
	gl::Uniform1i(location, value);
}

unsigned int GLShaderImpl::getLocation(const StringId& name) const
{
	auto foundIt = std::find(_names.begin(), _names.end(), name);
	if (foundIt != _names.end()) {
		auto id = std::distance(_names.begin(), foundIt);
		return _locations[id];
	}

	GLuint location = gl::GetUniformLocation(_programHandle, name.getChars());
	_names.push_back(name);
	_locations.push_back(location);
	return location;
}
