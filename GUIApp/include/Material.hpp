#pragma once
#include "IDrawable.hpp"
#include "glm/vec3.hpp"
#include <memory>

class Shader;

class Material
{
private:
	std::shared_ptr<Shader> _shader;
	glm::vec3 _mainColor;

public:
	Material();

	void setShader(const std::shared_ptr<Shader>& shader);
	void setMainColor(const glm::vec3& color);

	void apply(const DrawContext& context);
	void clear();
};
