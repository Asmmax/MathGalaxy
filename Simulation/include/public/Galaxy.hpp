#pragma once
#include <memory>

class IGalaxyRegistry;
class GalaxyRegistry;
class IView;

class Galaxy
{
protected:
	std::shared_ptr<GalaxyRegistry> _registry;
public:
	Galaxy();
	virtual ~Galaxy();

	virtual void step(double deltaTime) = 0;
	void gravity();
	void update(IView* view);
	IGalaxyRegistry* getRegistry();
};