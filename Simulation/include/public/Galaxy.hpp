#pragma once
#include <memory>

class IGalaxyRegistry;
class GalaxyRegistry;

class Galaxy
{
private:
	std::shared_ptr<GalaxyRegistry> _registry;
public:
	Galaxy();
	IGalaxyRegistry* getRegistry();

	void movement(double deltaTime);
	void gravity();
};