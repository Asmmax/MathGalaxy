#include "infrastruct/objects/Light.hpp"
#include "infrastruct/DrawState.hpp"
#include <string>

int Light::MAX_LIGHT_COUNT = 10;

Light::Light():
	_position(),
	_color(1.0f, 1.0f, 1.0f),
	_intensity(1.0f),
	_radius(100.0f),
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

void Light::setPosition(const glm::vec3& position)
{
	_position = position;
}

void Light::predraw(DrawStatePool& statePool)
{
	auto& state = statePool.get();

	static std::string nameTemplate = "PointLights";

	static StringId viewMatrixName = StringId("ViewMatrix");
	auto& viewMatrix = state.getMat4x4(viewMatrixName);
	glm::vec4 viewPosition = viewMatrix * glm::vec4(_position, 1.0f);

	int i = 0;
	for (; i < MAX_LIGHT_COUNT; i++) {
		std::string name(nameTemplate);
		name += "[" + std::to_string(i) + "]";

		if (!state.has((name + ".Position").c_str())) {
			state.add((name + ".Position").c_str(), viewPosition);
			state.add((name + ".Color").c_str(), _color);
			state.add((name + ".Intensity").c_str(), _intensity);
			state.add((name + ".Radius").c_str(), _radius);
			state.add((name + ".FadingArea").c_str(), _fadingArea);
			break;
		}
	}

	static StringId pointLightCountName = StringId("PointLightCount");
	state.addOrSet(pointLightCountName, i + 1);
}
