#include "infrastruct/DrawState.hpp"
#include "infrastruct/resources/Shader.hpp"
#include <assert.h>


void DrawState::add(const StringId& name, const glm::mat4& matrix)
{
	assert(!has(name));

	_4x4matrices.emplace_back(matrix);
	_4x4matrixNames.emplace_back(name);
}

void DrawState::add(const StringId& name, const glm::mat3& matrix)
{
	assert(!has(name));

	_3x3matrices.emplace_back(matrix);
	_3x3matrixNames.emplace_back(name);
}

void DrawState::add(const StringId& name, const glm::vec4& vector)
{
	assert(!has(name));

	_4vectors.emplace_back(vector);
	_4vectorNames.emplace_back(name);
}

void DrawState::add(const StringId& name, const glm::vec3& vector)
{
	assert(!has(name));

	_3vectors.emplace_back(vector);
	_3vectorNames.emplace_back(name);
}

void DrawState::add(const StringId& name, float value)
{
	assert(!has(name));

	_floatValues.emplace_back(value);
	_floatNames.emplace_back(name);
}

void DrawState::add(const StringId& name, int value)
{
	assert(!has(name));

	_intValues.emplace_back(value);
	_intNames.emplace_back(name);
}


void DrawState::addOrSet(const StringId& name, const glm::mat4& matrix)
{
	addOrSet(name, _4x4matrixNames, _4x4matrices, matrix);
}

void DrawState::addOrSet(const StringId& name, const glm::mat3& matrix)
{
	addOrSet(name, _3x3matrixNames, _3x3matrices, matrix);
}

void DrawState::addOrSet(const StringId& name, const glm::vec4& vector)
{
	addOrSet(name, _4vectorNames, _4vectors, vector);
}

void DrawState::addOrSet(const StringId& name, const glm::vec3& vector)
{
	addOrSet(name, _3vectorNames, _3vectors, vector);
}

void DrawState::addOrSet(const StringId& name, float value)
{
	addOrSet(name, _floatNames, _floatValues, value);
}

void DrawState::addOrSet(const StringId& name, int value)
{
	addOrSet(name, _intNames, _intValues, value);
}


void DrawState::set(const StringId& name, const glm::mat4& matrix)
{
	set(name, _4x4matrixNames, _4x4matrices, matrix);
}

void DrawState::set(const StringId& name, const glm::mat3& matrix)
{
	set(name, _3x3matrixNames, _3x3matrices, matrix);
}

void DrawState::set(const StringId& name, const glm::vec4& vector)
{
	set(name, _4vectorNames, _4vectors, vector);
}

void DrawState::set(const StringId& name, const glm::vec3& vector)
{
	set(name, _3vectorNames, _3vectors, vector);
}

void DrawState::set(const StringId& name, float value)
{
	set(name, _floatNames, _floatValues, value);
}

void DrawState::set(const StringId& name, int value)
{
	set(name, _intNames, _intValues, value);
}


void DrawState::remove(const StringId& name)
{
	if (remove(name, _4x4matrixNames, _4x4matrices)) {
		return;
	}

	if (remove(name, _3x3matrixNames, _3x3matrices)) {
		return;
	}

	if (remove(name, _4vectorNames, _4vectors)) {
		return;
	}

	if (remove(name, _3vectorNames, _3vectors)) {
		return;
	}

	if (remove(name, _floatNames, _floatValues)) {
		return;
	}

	if (remove(name, _intNames, _intValues)) {
		return;
	}
}


bool DrawState::has(const StringId& name) const
{
	if (std::find(_4x4matrixNames.begin(), _4x4matrixNames.end(), name) != _4x4matrixNames.end()) {
		return true;
	}

	if (std::find(_3x3matrixNames.begin(), _3x3matrixNames.end(), name) != _3x3matrixNames.end()) {
		return true;
	}

	if (std::find(_4vectorNames.begin(), _4vectorNames.end(), name) != _4vectorNames.end()) {
		return true;
	}

	if (std::find(_3vectorNames.begin(), _3vectorNames.end(), name) != _3vectorNames.end()) {
		return true;
	}

	if (std::find(_floatNames.begin(), _floatNames.end(), name) != _floatNames.end()) {
		return true;
	}

	if (std::find(_intNames.begin(), _intNames.end(), name) != _intNames.end()) {
		return true;
	}

	return false;
}


const glm::mat4& DrawState::getMat4x4(const StringId& name) const
{
	static glm::mat4 defaultValue;
	return getValue(name, _4x4matrixNames, _4x4matrices, defaultValue);
}

const glm::mat3& DrawState::getMat3x3(const StringId& name) const
{
	static glm::mat3 defaultValue;
	return getValue(name, _3x3matrixNames, _3x3matrices, defaultValue);
}

const glm::vec4& DrawState::getVector4(const StringId& name) const
{
	static glm::vec4 defaultValue;
	return getValue(name, _4vectorNames, _4vectors, defaultValue);
}

const glm::vec3& DrawState::getVector3(const StringId& name) const
{
	static glm::vec3 defaultValue;
	return getValue(name, _3vectorNames, _3vectors, defaultValue);
}

float DrawState::getFloat(const StringId& name) const
{
	static float defaultValue = 0.0f;
	return getValue(name, _floatNames, _floatValues, defaultValue);
}

int DrawState::getInt(const StringId& name) const
{
	static int defaultValue = 0;
	return getValue(name, _intNames, _intValues, defaultValue);
}


void DrawState::apply(Shader& shader) const
{
	for (size_t i = 0; i < _4x4matrices.size(); i++) {
		shader.setUniform(_4x4matrixNames[i], _4x4matrices[i]);
	}

	for (size_t i = 0; i < _3x3matrices.size(); i++) {
		shader.setUniform(_3x3matrixNames[i], _3x3matrices[i]);
	}

	for (size_t i = 0; i < _4vectors.size(); i++) {
		shader.setUniform(_4vectorNames[i], _4vectors[i]);
	}

	for (size_t i = 0; i < _3vectors.size(); i++) {
		shader.setUniform(_3vectorNames[i], _3vectors[i]);
	}

	for (size_t i = 0; i < _floatValues.size(); i++) {
		shader.setUniform(_floatNames[i], _floatValues[i]);
	}

	for (size_t i = 0; i < _intValues.size(); i++) {
		shader.setUniform(_intNames[i], _intValues[i]);
	}
}


void DrawState::apply(DrawState& otherState) const
{
	for (size_t i = 0; i < _4x4matrices.size(); i++) {
		otherState.add(_4x4matrixNames[i], _4x4matrices[i]);
	}

	for (size_t i = 0; i < _3x3matrices.size(); i++) {
		otherState.add(_3x3matrixNames[i], _3x3matrices[i]);
	}

	for (size_t i = 0; i < _4vectors.size(); i++) {
		otherState.add(_4vectorNames[i], _4vectors[i]);
	}

	for (size_t i = 0; i < _3vectors.size(); i++) {
		otherState.add(_3vectorNames[i], _3vectors[i]);
	}

	for (size_t i = 0; i < _floatValues.size(); i++) {
		otherState.add(_floatNames[i], _floatValues[i]);
	}

	for (size_t i = 0; i < _intValues.size(); i++) {
		otherState.add(_intNames[i], _intValues[i]);
	}
}


DrawStatePool::DrawStatePool(size_t size) :
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
