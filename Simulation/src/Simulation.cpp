#include "Simulation.hpp"
#include "World.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

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

}