#pragma once
#include "AMaterial.hpp"

class ColoredMaterial : public AMaterial
{
private:
	glm::vec3 _mainColor;

public:
	ColoredMaterial();

	void setMainColor(const glm::vec3& color);

protected:
	void applyImpl() override;

	static std::shared_ptr<Shader> defaultShader;
};
