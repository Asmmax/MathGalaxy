#include "schemes/VerletScheme.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

void VerletScheme::init(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc)
{
	step(deltaTime, pos, vel, acc);
}

void VerletScheme::step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc)
{
	pos.value += vel.value * deltaTime + acc.preValue * deltaTime * deltaTime / 2;
	vel.value += (acc.value + acc.preValue) * deltaTime / 2;
}
