#include "CentralDifferenceGalaxy.hpp"
#include "GalaxyRegistry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

CentralDifferenceGalaxy::CentralDifferenceGalaxy() :
	_isFirstStep(true)
{
}

void CentralDifferenceGalaxy::step(double deltaTime)
{
	if (_isFirstStep){
		startStep(deltaTime);
		_isFirstStep = false;
		return;
	}

	entt::registry& registry = _registry->getEnttRegistry();

	auto celestialBodies = registry.view<Position, Velocity, const Acceleration>();
	celestialBodies.each([deltaTime](Position& pos, Velocity& vel, const Acceleration& acc) {
		vel.value += acc.value * deltaTime;
		pos.value += vel.value * deltaTime;
		});

	gravity();
}

void CentralDifferenceGalaxy::startStep(double deltaTime)
{
	entt::registry& registry = _registry->getEnttRegistry();

	auto celestialBodies = registry.view<Position, Velocity, const Acceleration>();
	celestialBodies.each([deltaTime](Position& pos, Velocity& vel, const Acceleration& acc) {
		vel.value += acc.value * deltaTime / 2;
		pos.value += vel.value * deltaTime;
		});

	gravity();
}