#pragma once
#include "drawables/AMaterial.hpp"

class DiffusedMaterial : public AMaterial
{
private:
	glm::vec3 _diffuseColor;
	float _ambientFactor;
	float _diffuseFactor;

public:
	DiffusedMaterial(const std::shared_ptr<Shader>& shader);

	void setDiffuseColor(const glm::vec3& color);

	void setAmbientFactor(float factor);
	void setDiffuseFactor(float factor);

protected:
	void applyImpl() override;
};
