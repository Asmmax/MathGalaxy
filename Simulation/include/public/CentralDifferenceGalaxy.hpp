#pragma once
#include "Galaxy.hpp"

class CentralDifferenceGalaxy : public Galaxy
{
private:
	bool _isFirstStep;
public:
	CentralDifferenceGalaxy();
	void step(double deltaTime) override;
private:
	void startStep(double deltaTime);
};
