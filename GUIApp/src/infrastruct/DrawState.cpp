#include "infrastruct/DrawState.hpp"
#include "infrastruct/resources/Shader.hpp"
#include <assert.h>

void DrawState::add(const std::string& name, const glm::mat4& matrix)
{
	assert(!has(name));

	_names.emplace_back(name);
	_4x4matrices.emplace_back(matrix);
	_4x4matrixNames.emplace_back(_names.size() - 1);
}

void DrawState::add(const std::string& name, const glm::mat3& matrix)
{
	assert(!has(name));

	_names.emplace_back(name);
	_3x3matrices.emplace_back(matrix);
	_3x3matrixNames.emplace_back(_names.size() - 1);
}

void DrawState::add(const std::string& name, const glm::vec4& vector)
{
	assert(!has(name));

	_names.emplace_back(name);
	_4vectors.emplace_back(vector);
	_4vectorNames.emplace_back(_names.size() - 1);
}

void DrawState::add(const std::string& name, const glm::vec3& vector)
{
	assert(!has(name));

	_names.emplace_back(name);
	_3vectors.emplace_back(vector);
	_3vectorNames.emplace_back(_names.size() - 1);
}

void DrawState::add(const std::string& name, float value)
{
	assert(!has(name));

	_names.emplace_back(name);
	_floatValues.emplace_back(value);
	_floatNames.emplace_back(_names.size() - 1);
}

void DrawState::add(const std::string& name, int value)
{
	assert(!has(name));

	_names.emplace_back(name);
	_intValues.emplace_back(value);
	_intNames.emplace_back(_names.size() - 1);
}

void DrawState::set(const std::string& name, const glm::mat4& matrix)
{
	set(name, _4x4matrixNames, _4x4matrices, matrix);
}

void DrawState::set(const std::string& name, const glm::mat3& matrix)
{
	set(name, _3x3matrixNames, _3x3matrices, matrix);
}

void DrawState::set(const std::string& name, const glm::vec4& vector)
{
	set(name, _4vectorNames, _4vectors, vector);
}

void DrawState::set(const std::string& name, const glm::vec3& vector)
{
	set(name, _3vectorNames, _3vectors, vector);
}

void DrawState::set(const std::string& name, float value)
{
	set(name, _floatNames, _floatValues, value);
}

void DrawState::set(const std::string& name, int value)
{
	set(name, _intNames, _intValues, value);
}

void DrawState::remove(const std::string& name)
{
	auto foundIt = std::find(_names.begin(), _names.end(), name);
	if (foundIt == _names.end()) {
		return;
	}

	size_t nameIndex = std::distance(_names.begin(), foundIt);
	_names.erase(foundIt);

	if (remove(nameIndex, _4x4matrixNames, _4x4matrices)) {
		return;
	}

	if (remove(nameIndex, _3x3matrixNames, _3x3matrices)) {
		return;
	}

	if (remove(nameIndex, _4vectorNames, _4vectors)) {
		return;
	}

	if (remove(nameIndex, _3vectorNames, _3vectors)) {
		return;
	}

	if (remove(nameIndex, _floatNames, _floatValues)) {
		return;
	}

	if (remove(nameIndex, _intNames, _intValues)) {
		return;
	}
}

bool DrawState::has(const std::string& name) const
{
	return std::find(_names.begin(), _names.end(), name) != _names.end();
}

const glm::mat4& DrawState::getMat4x4(const std::string& name) const
{
	static glm::mat4 defaultValue;
	return getValue(name, _4x4matrixNames, _4x4matrices, defaultValue);
}

const glm::mat3& DrawState::getMat3x3(const std::string& name) const
{
	static glm::mat3 defaultValue;
	return getValue(name, _3x3matrixNames, _3x3matrices, defaultValue);
}

const glm::vec4& DrawState::getVector4(const std::string& name) const
{
	static glm::vec4 defaultValue;
	return getValue(name, _4vectorNames, _4vectors, defaultValue);
}

const glm::vec3& DrawState::getVector3(const std::string& name) const
{
	static glm::vec3 defaultValue;
	return getValue(name, _3vectorNames, _3vectors, defaultValue);
}

float DrawState::getFloat(const std::string& name) const
{
	static float defaultValue = 0.0f;
	return getValue(name, _floatNames, _floatValues, defaultValue);
}

int DrawState::getInt(const std::string& name) const
{
	static int defaultValue = 0;
	return getValue(name, _intNames, _intValues, defaultValue);
}

void DrawState::apply(Shader& shader) const
{
	for (size_t i = 0; i < _4x4matrices.size(); i++) {
		shader.setUniform(_names[_4x4matrixNames[i]], _4x4matrices[i]);
	}

	for (size_t i = 0; i < _3x3matrices.size(); i++) {
		shader.setUniform(_names[_3x3matrixNames[i]], _3x3matrices[i]);
	}

	for (size_t i = 0; i < _4vectors.size(); i++) {
		shader.setUniform(_names[_4vectorNames[i]], _4vectors[i]);
	}

	for (size_t i = 0; i < _3vectors.size(); i++) {
		shader.setUniform(_names[_3vectorNames[i]], _3vectors[i]);
	}

	for (size_t i = 0; i < _floatValues.size(); i++) {
		shader.setUniform(_names[_floatNames[i]], _floatValues[i]);
	}

	for (size_t i = 0; i < _intValues.size(); i++) {
		shader.setUniform(_names[_intNames[i]], _intValues[i]);
	}
}

void DrawState::apply(DrawState& otherState) const
{
	for (size_t i = 0; i < _4x4matrices.size(); i++) {
		otherState.add(_names[_4x4matrixNames[i]], _4x4matrices[i]);
	}

	for (size_t i = 0; i < _3x3matrices.size(); i++) {
		otherState.add(_names[_3x3matrixNames[i]], _3x3matrices[i]);
	}

	for (size_t i = 0; i < _4vectors.size(); i++) {
		otherState.add(_names[_4vectorNames[i]], _4vectors[i]);
	}

	for (size_t i = 0; i < _3vectors.size(); i++) {
		otherState.add(_names[_3vectorNames[i]], _3vectors[i]);
	}

	for (size_t i = 0; i < _floatValues.size(); i++) {
		otherState.add(_names[_floatNames[i]], _floatValues[i]);
	}

	for (size_t i = 0; i < _intValues.size(); i++) {
		otherState.add(_names[_intNames[i]], _intValues[i]);
	}
}

DrawStatePool::DrawStatePool(size_t size):
	_cursor(0)
{
	assert(size > 1);
	_pool.resize(size > 1 ? size : 1);
}

DrawState& DrawStatePool::get()
{
	return _pool[_cursor];
}

void DrawStatePool::push()
{
	assert(_cursor < _pool.size() - 1);
	_cursor++;
	_pool[_cursor] = _pool[_cursor - 1];
}

void DrawStatePool::pop()
{
	assert(_cursor > 0);
	_cursor--;
}
