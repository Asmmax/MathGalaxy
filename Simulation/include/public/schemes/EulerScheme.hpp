#pragma once
#include "IDifferenceScheme.hpp"

class EulerScheme : public IDifferenceScheme
{
public:
	void step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc) override;
};