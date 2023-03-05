#pragma once
#include "AMaterial.hpp"

class SkyMaterial : public AMaterial
{
private:
	glm::vec3 _baseColor;

public:
	SkyMaterial(const std::shared_ptr<Shader>& shader);

	void setBaseColor(const glm::vec3& color);

protected:
	void applyImpl() override;
};
