#pragma once
#include "IWorld.hpp"
#include "entt.hpp"

class World : public IWorld
{
private:
	entt::registry _registry;
public:
	int createEntity() override;

	Acceleration& attach(int entity, const Acceleration& acc) override;
	Mass& attach(int entity, const Mass& mass) override;
	Position& attach(int entity, const Position& pos) override;
	Velocity& attach(int entity, const Velocity& vel) override;

	inline const entt::registry& getRegistry() const { return _registry; }
};