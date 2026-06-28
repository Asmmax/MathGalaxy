#include "drawables/Scene.hpp"

#include "RenderData.hpp"
#include "drawables/Camera.hpp"
#include "drawables/CelestialSystem.hpp"
#include "drawables/Transform.hpp"


Scene::Scene()
{
	_root = std::make_shared<Transform>();
}

Scene::~Scene() = default;

void Scene::setCelestialSystem(std::unique_ptr<CelestialSystem> celSystem)
{
	_root->addChild(celSystem->getTransform());
	_celSystem = std::move(celSystem);
}

void Scene::setCamera(const std::shared_ptr<Camera>& camera)
{
	_root->addChild(camera->getTargetTransform());
	_camera = camera;
}

void Scene::draw(RenderQueue& renderQueue, RenderData& frameData)
{
	_root->computeGlobalMatrices();
	frameData.setVec3(StringId("AmbientColor"), glm::vec3(0.2f, 0.1f, 0.1f));

	_celSystem->preDraw(frameData);

	_celSystem->draw(renderQueue);
	_camera->draw(renderQueue);
}
