#pragma once
#include "Galaxy.hpp"

class EulerKromerGalaxy : public Galaxy
{
public:
	void step(double deltaTime) override;
};
