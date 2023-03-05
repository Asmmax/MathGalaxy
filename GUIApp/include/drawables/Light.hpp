#pragma once
#include "Node.hpp"
#include "glm/glm.hpp"

class Light : public Node
{
private:
	glm::vec3 _color;
	float _intensity;
	float _radius;
	float _fadingArea;

public:
	Light(float radius = 100.0f);

	void setColor(const glm::vec3& color);
	void setIntensity(float intensity);
	void setRadius(float radius);
	void setFadingArea(float fadingArea);

	void init() override;
	void predraw(DrawContext& context) override;
	void draw(DrawContext& context) override;

	static int MAX_LIGHT_COUNT;
};
