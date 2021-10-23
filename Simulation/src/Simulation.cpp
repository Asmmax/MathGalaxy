#include "Simulation.hpp"
#include "World.hpp"

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
	const entt::registry& registry = _world->getRegistry();

}

void Simulation::gravity()
{
	const entt::registry& registry = _world->getRegistry();

}