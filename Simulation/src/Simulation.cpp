#include "Simulation.hpp"
#include "World.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "components/Mass.hpp"

#include <cmath>

const double gravConst = 6.6743e-11;

Simulation::Simulation():
	_world(new World())
{
}

IWorld* Simulation::getWorld()
{
	return _world.get();
}

void Simulation::movement(double deltaTime)
{
	entt::registry& registry = _world->getRegistry();

	auto celestialBodies = registry.view<Position, Velocity, const Acceleration>();

	celestialBodies.each([deltaTime](Position& pos, Velocity& vel, const Acceleration& acc) {
		pos.value += vel.value * deltaTime;
		vel.value += acc.value * deltaTime;
		});
}

void Simulation::gravity()
{
	entt::registry& registry = _world->getRegistry();

	auto celestialBodies = registry.view<Acceleration, const Position, const Mass>();

	for (auto firstBody : celestialBodies) {
		auto& firstAcc = celestialBodies.get<Acceleration>(firstBody);
		auto& firstPos = celestialBodies.get<const Position>(firstBody);

		for (auto secondBody : celestialBodies) {

			if (firstBody == secondBody)
				continue;

			auto& secondPos = celestialBodies.get<const Position>(secondBody);
			auto& secondMass = celestialBodies.get<const Mass>(secondBody);

			Vector dir = secondPos.value - firstPos.value;
			firstAcc.value = gravConst * secondMass.value * dir / (dir.length() * dir.sqrLength());
		}
	}
}