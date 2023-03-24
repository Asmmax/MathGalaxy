#pragma once
#include "infrastruct/StringId.hpp"
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
	std::vector<StringId> _4x4matrixNames;
	std::vector<StringId> _3x3matrixNames;
	std::vector<StringId> _4vectorNames;
	std::vector<StringId> _3vectorNames;
	std::vector<StringId> _floatNames;
	std::vector<StringId> _intNames;

	std::vector<glm::mat4> _4x4matrices;
	std::vector<glm::mat3> _3x3matrices;
	std::vector<glm::vec4> _4vectors;
	std::vector<glm::vec3> _3vectors;
	std::vector<float> _floatValues;
	std::vector<int> _intValues;

public:
	void add(const StringId& name, const glm::mat4& matrix);
	void add(const StringId& name, const glm::mat3& matrix);
	void add(const StringId& name, const glm::vec4& vector);
	void add(const StringId& name, const glm::vec3& vector);
	void add(const StringId& name, float value);
	void add(const StringId& name, int value);

	void addOrSet(const StringId& name, const glm::mat4& matrix);
	void addOrSet(const StringId& name, const glm::mat3& matrix);
	void addOrSet(const StringId& name, const glm::vec4& vector);
	void addOrSet(const StringId& name, const glm::vec3& vector);
	void addOrSet(const StringId& name, float value);
	void addOrSet(const StringId& name, int value);

	void set(const StringId& name, const glm::mat4& matrix);
	void set(const StringId& name, const glm::mat3& matrix);
	void set(const StringId& name, const glm::vec4& vector);
	void set(const StringId& name, const glm::vec3& vector);
	void set(const StringId& name, float value);
	void set(const StringId& name, int value);

	void remove(const StringId& name);

	bool has(const StringId& name) const;

	const glm::mat4& getMat4x4(const StringId& name) const;
	const glm::mat3& getMat3x3(const StringId& name) const;
	const glm::vec4& getVector4(const StringId& name) const;
	const glm::vec3& getVector3(const StringId& name) const;
	float getFloat(const StringId& name) const;
	int getInt(const StringId& name) const;

	void apply(Shader& shader) const;
	void apply(DrawState& otherState) const;

private:
	template<typename Type>
	bool remove(const StringId& name, std::vector<StringId>& names, std::vector<Type>& values)
	{
		auto nameIt = std::find(names.begin(), names.end(), name);
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
	const Type& getValue(const StringId& name, const std::vector<StringId>& names, const std::vector<Type>& values, const Type& defaultValue) const
	{
		assert(has(name));

		auto foundIt = std::find(names.begin(), names.end(), name);
		if (foundIt == names.end()) {
			return defaultValue;
		}

		size_t index = std::distance(names.begin(), foundIt);
		return values[index];
	}

	template<typename Type>
	void addOrSet(const StringId& name, const std::vector<StringId>& names, std::vector<Type>& values, const Type& newValue)
	{
		auto foundIt = std::find(names.begin(), names.end(), name);
		if (foundIt == names.end()) {
			add(name, newValue);
			return;
		}

		size_t index = std::distance(names.begin(), foundIt);
		values[index] = newValue;
	}

	template<typename Type>
	void set(const StringId& name, const std::vector<StringId>& names, std::vector<Type>& values, const Type& newValue)
	{
		assert(has(name));

		auto foundIt = std::find(names.begin(), names.end(), name);
		if (foundIt == names.end()) {
			return;
		}

		size_t index = std::distance(names.begin(), foundIt);
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
