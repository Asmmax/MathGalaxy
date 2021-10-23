#pragma once
#include <memory>

class IWorld;
class World;

class Simulation
{
private:
	std::shared_ptr<World> _world;
public:
	Simulation();
	IWorld* getWorld();

	void movement(double deltaTime);
	void gravity();
};