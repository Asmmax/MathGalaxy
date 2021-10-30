#include "EulerGalaxy.hpp"
#include "GalaxyRegistry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

void EulerGalaxy::step(double deltaTime)
{
	entt::registry& registry = _registry->getEnttRegistry();

	auto celestialBodies = registry.view<Position, Velocity, const Acceleration>();
	celestialBodies.each([deltaTime](Position& pos, Velocity& vel, const Acceleration& acc) {
		pos.value += vel.value * deltaTime;
		vel.value += acc.value * deltaTime;
		});

	gravity();
}