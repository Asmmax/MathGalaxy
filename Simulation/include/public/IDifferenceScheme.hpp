#pragma once
#include <memory>

struct Position;
struct Velocity;
struct Acceleration;

class IDifferenceScheme
{
public:
	virtual ~IDifferenceScheme() {}
	virtual void init(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc) = 0;
	virtual void step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc) = 0;
};