#include "drawables/CelestialSystem.hpp"

#include "drawables/Transform.hpp"
#include "drawables/CelestialBody.hpp"

CelestialSystem::CelestialSystem()
{
	_transform = std::make_shared<Transform>();
}

CelestialSystem::~CelestialSystem() = default;

void CelestialSystem::addBody(std::unique_ptr<CelestialBody> body)
{
	_transform->addChild(body->getTransform());
	_bodies.push_back(std::move(body));
}

void CelestialSystem::preDraw(RenderData& frameData)
{
	for (auto& body : _bodies) {
		body->preDraw(frameData);
	}
}

void CelestialSystem::draw(RenderQueue& renderQueue)
{
	for (auto& body : _bodies) {
		body->draw(renderQueue);
	}
}
