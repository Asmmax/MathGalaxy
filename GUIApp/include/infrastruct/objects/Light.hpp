#pragma once
#include "infrastruct/DrawState.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>


class Light
{
private:
	glm::vec3 _position;
	glm::vec3 _color;
	float _intensity;
	float _radius;
	float _fadingArea;

public:
	Light();

	void setColor(const glm::vec3& color);
	void setIntensity(float intensity);
	void setRadius(float radius);
	void setFadingArea(float fadingArea);
	void setPosition(const glm::vec3& position);

	void predraw(DrawStatePoolDef& statePool);

	static int MAX_LIGHT_COUNT;
};