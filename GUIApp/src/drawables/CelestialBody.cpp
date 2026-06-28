#include "drawables/CelestialBody.hpp"

#include "drawables/Light.hpp"
#include "drawables/Transform.hpp"
#include "RenderQueue.hpp"


CelestialBody::CelestialBody()
{
	_transform = std::make_shared<Transform>();
}

CelestialBody::~CelestialBody() = default;

void CelestialBody::setShader(Shader* shader)
{
	_shader = shader;
}

void CelestialBody::setMaterial(Material* material)
{
	_material = material;
}

void CelestialBody::setMesh(Mesh* mesh)
{
	_mesh = mesh;
}

void CelestialBody::setLight(std::unique_ptr<Light> light)
{
	_transform->addChild(light->getTransform());
	_light = std::move(light);
}

void CelestialBody::preDraw(RenderData& frameData)
{
	if (_light)
	{
		_light->preDraw(frameData);
	}
}

void CelestialBody::draw(RenderQueue& renderQueue)
{
	RenderCommand solarCmd;
	solarCmd.shader = _shader;
	solarCmd.material = _material;
	solarCmd.mesh = _mesh;
	solarCmd.modelMatrix = _transform->getGlobalMatrix();
	renderQueue.submit(solarCmd);
}
