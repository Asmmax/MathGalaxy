#pragma once
#include "IDifferenceScheme.hpp"

class EulerScheme : public IDifferenceScheme
{
public:
	void init(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc) override;
	void step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc) override;
};