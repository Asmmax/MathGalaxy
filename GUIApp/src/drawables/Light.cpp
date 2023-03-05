#include "drawables/Light.hpp"
#include "Transform.hpp"
#include "DrawContext.hpp"

int Light::MAX_LIGHT_COUNT = 10;

Light::Light(float radius):
	_color(1.0f, 1.0f, 1.0f),
	_intensity(1.0f),
	_radius(radius),
	_fadingArea(0.0f)
{
}

void Light::setColor(const glm::vec3& color)
{
	_color = color;
}

void Light::setIntensity(float intensity)
{
	_intensity = intensity;
}

void Light::setRadius(float radius)
{
	_radius = radius;
}

void Light::setFadingArea(float fadingArea)
{
	_fadingArea = fadingArea;
}

void Light::init()
{
}

void Light::predraw(DrawContext& context)
{
	std::string nameTemplate = "PointLights";

	auto viewMatrix = context.getMat4x4("ViewMatrix");
	glm::vec3 globalPosition = getTransform()->getGlobalPosition();
	glm::vec4 viewPosition = viewMatrix * glm::vec4(globalPosition, 1.0f);

	int i = 0;
	for (; i < MAX_LIGHT_COUNT; i++) {
		std::string name(nameTemplate);
		name += "[" + std::to_string(i) + "]";

		if (!context.has(name + ".Position")) {
			context.add(name + ".Position", viewPosition);
			context.add(name + ".Color", _color);
			context.add(name + ".Intensity", _intensity);
			context.add(name + ".Radius", _radius);
			context.add(name + ".FadingArea", _fadingArea);
			break;
		}
	}

	context.remove("PointLightCount");
	context.add("PointLightCount", i + 1);
}

void Light::draw(DrawContext& context)
{
}
