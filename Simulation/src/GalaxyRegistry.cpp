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

const Acceleration& GalaxyRegistry::attach(int entity, const Acceleration& acc)
{
	return _registry.emplace<Acceleration>(static_cast<entt::entity>(entity), acc);
}

const Position& GalaxyRegistry::attach(int entity, const Position& pos)
{
	return _registry.emplace<Position>(static_cast<entt::entity>(entity), pos);
}

const Velocity& GalaxyRegistry::attach(int entity, const Velocity& vel)
{
	return _registry.emplace<Velocity>(static_cast<entt::entity>(entity), vel);
}
