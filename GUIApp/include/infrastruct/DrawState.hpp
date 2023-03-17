#pragma once
#include "glm/glm.hpp"
#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>

class Shader;

class DrawState
{
private:
	std::vector<std::string> _names;

	std::vector<size_t> _4x4matrixNames;
	std::vector<size_t> _3x3matrixNames;
	std::vector<size_t> _4vectorNames;
	std::vector<size_t> _3vectorNames;
	std::vector<size_t> _floatNames;
	std::vector<size_t> _intNames;

	std::vector<glm::mat4> _4x4matrices;
	std::vector<glm::mat3> _3x3matrices;
	std::vector<glm::vec4> _4vectors;
	std::vector<glm::vec3> _3vectors;
	std::vector<float> _floatValues;
	std::vector<int> _intValues;

public:
	void add(const std::string& name, const glm::mat4& matrix);
	void add(const std::string& name, const glm::mat3& matrix);
	void add(const std::string& name, const glm::vec4& vector);
	void add(const std::string& name, const glm::vec3& vector);
	void add(const std::string& name, float value);
	void add(const std::string& name, int value);

	void set(const std::string& name, const glm::mat4& matrix);
	void set(const std::string& name, const glm::mat3& matrix);
	void set(const std::string& name, const glm::vec4& vector);
	void set(const std::string& name, const glm::vec3& vector);
	void set(const std::string& name, float value);
	void set(const std::string& name, int value);

	void remove(const std::string& name);

	bool has(const std::string& name) const;

	const glm::mat4& getMat4x4(const std::string& name) const;
	const glm::mat3& getMat3x3(const std::string& name) const;
	const glm::vec4& getVector4(const std::string& name) const;
	const glm::vec3& getVector3(const std::string& name) const;
	float getFloat(const std::string& name) const;
	int getInt(const std::string& name) const;

	void apply(Shader& shader) const;
	void apply(DrawState& otherState) const;

private:
	template<typename Type>
	bool remove(size_t nameIndex, std::vector<size_t>& names, std::vector<Type>& values)
	{
		auto nameIt = std::find(names.begin(), names.end(), nameIndex);
		if (nameIt == names.end()) {
			return false;
		}

		size_t index = std::distance(names.begin(), nameIt);

		auto valueIt = values.begin();
		std::advance(valueIt, index);

		names.erase(nameIt);
		values.erase(valueIt);
		return true;
	}

	template<typename Type>
	const Type& getValue(const std::string& name, const std::vector<size_t>& names, const std::vector<Type>& values, const Type& defaultValue) const
	{
		assert(has(name));

		auto foundIt = std::find(_names.begin(), _names.end(), name);
		if (foundIt == _names.end()) {
			return defaultValue;
		}

		size_t nameIndex = std::distance(_names.begin(), foundIt);

		auto nameIt = std::find(names.begin(), names.end(), nameIndex);
		if (nameIt == names.end()) {
			assert(false);
			return defaultValue;
		}

		size_t index = std::distance(names.begin(), nameIt);

		return values[index];
	}

	template<typename Type>
	void set(const std::string& name, const std::vector<size_t>& names, std::vector<Type>& values, const Type& newValue)
	{
		assert(has(name));

		auto foundIt = std::find(_names.begin(), _names.end(), name);
		if (foundIt == _names.end()) {
			return;
		}

		size_t nameIndex = std::distance(_names.begin(), foundIt);

		auto nameIt = std::find(names.begin(), names.end(), nameIndex);
		if (nameIt == names.end()) {
			assert(false);
			return;
		}

		size_t index = std::distance(names.begin(), nameIt);

		values[index] = newValue;
	}
};

class DrawStatePool
{
private:
	std::vector<DrawState> _pool;
	size_t _cursor;
public:
	DrawStatePool(size_t size);

	DrawState& get();

	void push();
	void pop();
};
