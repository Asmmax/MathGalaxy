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
		pos.x += vel.x * deltaTime;
		pos.y += vel.y * deltaTime;
		pos.z += vel.z * deltaTime;

		vel.x += acc.x * deltaTime;
		vel.y += acc.y * deltaTime;
		vel.z += acc.z * deltaTime;
		});
}

void Simulation::gravity()
{
	entt::registry& registry = _world->getRegistry();

	auto celestialBodies = registry.view<Acceleration, const Position, const Mass>();

	for (auto firstBody : celestialBodies) {
		auto& firstAcc = celestialBodies.get<Acceleration>(firstBody);
		auto& firstPos = celestialBodies.get<const Position>(firstBody);
		auto& firstMass = celestialBodies.get<const Mass>(firstBody);

		for (auto secondBody : celestialBodies) {

			if (firstBody == secondBody)
				continue;

			auto& secondAcc = celestialBodies.get<Acceleration>(secondBody);
			auto& secondPos = celestialBodies.get<const Position>(secondBody);
			auto& secondMass = celestialBodies.get<const Mass>(secondBody);

			double dirX = secondPos.x - firstPos.x;
			double dirY = secondPos.y - firstPos.y;
			double dirZ = secondPos.z - firstPos.z;

			double dirLength = sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);

			firstAcc.x = gravConst * secondMass.value * dirX / (dirLength * dirLength * dirLength);
			firstAcc.y = gravConst * secondMass.value * dirY / (dirLength * dirLength * dirLength);
			firstAcc.z = gravConst * secondMass.value * dirZ / (dirLength * dirLength * dirLength);
		}
	}
}