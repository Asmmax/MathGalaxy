#include "EulerKromerGalaxy.hpp"
#include "GalaxyRegistry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

void EulerKromerGalaxy::step(double deltaTime)
{
	entt::registry& registry = _registry->getEnttRegistry();

	auto celestialBodies = registry.view<Position, Velocity, const Acceleration>();
	celestialBodies.each([deltaTime](Position& pos, Velocity& vel, const Acceleration& acc) {
		vel.value += acc.value * deltaTime;
		pos.value += vel.value * deltaTime;
		});

	gravity();
}