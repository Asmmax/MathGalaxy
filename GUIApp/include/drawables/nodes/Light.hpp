#pragma once
#include "drawables/nodes/Node.hpp"
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

	void init(const std::weak_ptr<IGraphicsContext>& context) override;
	void deinit() override;
	void predraw(DrawContext& context) override;
	void draw(const DrawContext& context) override;

	static int MAX_LIGHT_COUNT;
};
