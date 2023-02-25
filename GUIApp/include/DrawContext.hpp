#pragma once
#include "glm/glm.hpp"
#include <map>
#include <set>
#include <string>
#include <memory>

class Shader;

class DrawContext
{
private:
	std::set<std::string> _names;
	std::map<std::string, glm::mat4> _4x4matrices;
	std::map<std::string, glm::mat3> _3x3matrices;
	std::map<std::string, glm::vec4> _4vectors;
	std::map<std::string, glm::vec3> _3vectors;
	std::map<std::string, int> _intValues;

public:
	void add(const std::string& name, const glm::mat4& matrix);
	void add(const std::string& name, const glm::mat3& matrix);
	void add(const std::string& name, const glm::vec4& vector);
	void add(const std::string& name, const glm::vec3& vector);
	void add(const std::string& name, int value);

	void remove(const std::string& name);

	bool has(const std::string& name) const;

	const glm::mat4& getMat4x4(const std::string& name) const;
	const glm::mat3& getMat3x3(const std::string& name) const;
	const glm::vec4& getVector4(const std::string& name) const;
	const glm::vec3& getVector3(const std::string& name) const;
	int getInt(const std::string& name) const;

	void apply(Shader& shader) const;
};
