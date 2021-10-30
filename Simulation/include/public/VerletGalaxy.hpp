#pragma once
#include "Galaxy.hpp"
#include "Vector.hpp"
#include <vector>

class VerletGalaxy : public Galaxy
{
public:
	void step(double deltaTime) override;
private:
	void storeAccelerations();
};
