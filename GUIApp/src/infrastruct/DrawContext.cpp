#include "infrastruct/DrawContext.hpp"
#include "infrastruct/Shader.hpp"
#include <assert.h>

void DrawContext::add(const std::string& name, const glm::mat4& matrix)
{
	if (has(name)) {
		assert(false);
		return;
	}

	_4x4matrices[name] = matrix;
	_names.emplace(name);
}

void DrawContext::add(const std::string& name, const glm::mat3& matrix)
{
	if (has(name)) {
		assert(false);
		return;
	}

	_3x3matrices[name] = matrix;
	_names.emplace(name);
}

void DrawContext::add(const std::string& name, const glm::vec4& vector)
{
	if (has(name)) {
		assert(false);
		return;
	}

	_4vectors[name] = vector;
	_names.emplace(name);
}

void DrawContext::add(const std::string& name, const glm::vec3& vector)
{
	if (has(name)) {
		assert(false);
		return;
	}

	_3vectors[name] = vector;
	_names.emplace(name);
}

void DrawContext::add(const std::string& name, float value)
{
	if (has(name)) {
		assert(false);
		return;
	}

	_floatValues[name] = value;
	_names.emplace(name);
}

void DrawContext::add(const std::string& name, int value)
{
	if (has(name)) {
		assert(false);
		return;
	}

	_intValues[name] = value;
	_names.emplace(name);
}

void DrawContext::remove(const std::string& name)
{
	if (!has(name)) {
		return;
	}

	_names.erase(name);
	_4x4matrices.erase(name);
	_3x3matrices.erase(name);
	_4vectors.erase(name);
	_3vectors.erase(name);
	_intValues.erase(name);
}

bool DrawContext::has(const std::string& name) const
{
	return _names.find(name) != _names.end();
}

const glm::mat4& DrawContext::getMat4x4(const std::string& name) const
{
	assert(has(name));
	return _4x4matrices.at(name);
}

const glm::mat3& DrawContext::getMat3x3(const std::string& name) const
{
	assert(has(name));
	return _3x3matrices.at(name);
}

const glm::vec3& DrawContext::getVector3(const std::string& name) const
{
	assert(has(name));
	return _3vectors.at(name);
}

const glm::vec4& DrawContext::getVector4(const std::string& name) const
{
	assert(has(name));
	return _4vectors.at(name);
}

float DrawContext::getFloat(const std::string& name) const
{
	assert(has(name));
	return _floatValues.at(name);
}

int DrawContext::getInt(const std::string& name) const
{
	assert(has(name));
	return _intValues.at(name);
}

void DrawContext::apply(Shader& shader) const
{
	for (auto& value : _4x4matrices) {
		shader.setUniform(value.first, value.second);
	}

	for (auto& value : _3x3matrices) {
		shader.setUniform(value.first, value.second);
	}

	for (auto& value : _4vectors) {
		shader.setUniform(value.first, value.second);
	}

	for (auto& value : _3vectors) {
		shader.setUniform(value.first, value.second);
	}

	for (auto& value : _floatValues) {
		shader.setUniform(value.first, value.second);
	}

	for (auto& value : _intValues) {
		shader.setUniform(value.first, value.second);
	}
}
