#include "drawables/Light.hpp"

#include "drawables/Transform.hpp"
#include "RenderData.hpp"
#include "StringId.hpp"


Light::Light()
{
	_transform = std::make_shared<Transform>();
}


void Light::preDraw(RenderData& frameData)
{
	frameData.setInt(StringId("PointLightCount"), 1);
	frameData.setVec3(StringId("PointLights[0].Position"), _transform->getGlobalPosition());
	frameData.setVec3(StringId("PointLights[0].Color"), glm::vec3(1.0f, 1.0f, 1.0f));
	frameData.setFloat(StringId("PointLights[0].Intensity"), 1.0f);
	frameData.setFloat(StringId("PointLights[0].Radius"), 100.0f);
	frameData.setFloat(StringId("PointLights[0].FadingArea"), 0.0f);
}
