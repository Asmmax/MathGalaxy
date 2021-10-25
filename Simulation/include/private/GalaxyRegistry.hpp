#pragma once
#include "IGalaxyRegistry.hpp"
#include "entt.hpp"

class GalaxyRegistry : public IGalaxyRegistry
{
private:
	entt::registry _registry;
public:
	int createEntity() override;

	void attach(int entity, const Mass& mass) override;
	void attach(int entity, const Acceleration& acc) override;
	void attach(int entity, const Position& pos) override;
	void attach(int entity, const Velocity& vel) override;

	inline entt::registry& getEnttRegistry() { return _registry; }
};