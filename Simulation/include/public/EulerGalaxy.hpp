#pragma once
#include "Galaxy.hpp"

class EulerGalaxy : public Galaxy
{
public:
	void step(double deltaTime) override;
};
