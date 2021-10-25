#include "GalaxyRegistry.hpp"
#include "components/Acceleration.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Mass.hpp"

int GalaxyRegistry::createEntity()
{
	return static_cast<int>(_registry.create());
}

void GalaxyRegistry::attach(int entity, const Mass& mass)
{
	_registry.emplace<Mass>(static_cast<entt::entity>(entity), mass);
}

void GalaxyRegistry::attach(int entity, const Acceleration& acc)
{
	_registry.emplace<Acceleration>(static_cast<entt::entity>(entity), acc);
}

void GalaxyRegistry::attach(int entity, const Position& pos)
{
	_registry.emplace<Position>(static_cast<entt::entity>(entity), pos);
}

void GalaxyRegistry::attach(int entity, const Velocity& vel)
{
	_registry.emplace<Velocity>(static_cast<entt::entity>(entity), vel);
}
