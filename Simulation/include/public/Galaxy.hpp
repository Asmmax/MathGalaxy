#pragma once
#include <memory>

class IGalaxyRegistry;
class GalaxyRegistry;
class IView;
class IDifferenceScheme;

class Galaxy
{
private:
	std::shared_ptr<GalaxyRegistry> _registry;
	std::shared_ptr<IDifferenceScheme> _scheme;
public:
	Galaxy(const std::shared_ptr<IDifferenceScheme>& scheme = nullptr);
	IGalaxyRegistry* getRegistry();

	void start(double deltaTime);
	void movement(double deltaTime);
	void gravity();
	void update(IView* view);
};