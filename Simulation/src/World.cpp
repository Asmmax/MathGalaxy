#include "World.hpp"
#include "components/Acceleration.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Mass.hpp"

int World::createEntity()
{
	return static_cast<int>(_registry.create());
}

Acceleration& World::attach(int entity, const Acceleration& acc)
{
	return _registry.emplace<Acceleration>(static_cast<entt::entity>(entity), acc);
}

Mass& World::attach(int entity, const Mass& mass)
{
	return _registry.emplace<Mass>(static_cast<entt::entity>(entity), mass);
}

Position& World::attach(int entity, const Position& pos)
{
	return _registry.emplace<Position>(static_cast<entt::entity>(entity), pos);
}

Velocity& World::attach(int entity, const Velocity& vel)
{
	return _registry.emplace<Velocity>(static_cast<entt::entity>(entity), vel);
}
