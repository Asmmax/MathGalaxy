#pragma once
#include "IWorld.hpp"
#include "entt.hpp"

class World : public IWorld
{
private:
	entt::registry _registry;
public:
	int createEntity() override;

	void attach(int entity, const Mass& mass) override;
	const Acceleration& attach(int entity, const Acceleration& acc) override;
	const Position& attach(int entity, const Position& pos) override;
	const Velocity& attach(int entity, const Velocity& vel) override;

	inline entt::registry& getRegistry() { return _registry; }
};