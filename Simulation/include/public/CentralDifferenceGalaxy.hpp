#pragma once
#include "Galaxy.hpp"

class CentralDifferenceGalaxy : public Galaxy
{
public:
	void step(double deltaTime) override;
private:
	void initHalfStep(double deltaTime);
};
