#include "drawables/Light.hpp"
#include "Transform.hpp"
#include "DrawContext.hpp"

int Light::MAX_LIGHT_COUNT = 10;

void Light::init()
{

}

void Light::predraw(DrawContext& context)
{
	std::string nameTemplate = "LightPositions";

	int i = 0;
	for (; i < MAX_LIGHT_COUNT; i++) {
		std::string name(nameTemplate);
		name += "[" + std::to_string(i) + "]";

		if (!context.has(name)) {
			context.add(name, glm::vec4(getTransform()->getGlobalPosition(), 1.0f));
			break;
		}
	}

	context.remove("LightCount");
	context.add("LightCount", i + 1);
}

void Light::draw(DrawContext& context)
{
}
