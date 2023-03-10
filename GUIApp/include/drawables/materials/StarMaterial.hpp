#pragma once
#include "drawables/AMaterial.hpp"

class StarMaterial : public AMaterial
{
private:
	glm::vec3 _baseColor;
	glm::vec3 _boundColor;
	glm::vec3 _spaceColor;

public:
	StarMaterial(const std::shared_ptr<Shader>& shader);

	void setBaseColor(const glm::vec3& color);
	void setBoundColor(const glm::vec3& color);
	void setSpaceColor(const glm::vec3& color);

protected:
	void applyImpl() override;
};
