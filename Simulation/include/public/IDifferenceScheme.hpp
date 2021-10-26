#pragma once

struct Position;
struct Velocity;
struct Acceleration;

class IDifferenceScheme
{
public:
	virtual ~IDifferenceScheme() {}
	virtual void step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc) = 0;
};