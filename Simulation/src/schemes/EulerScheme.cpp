#include "schemes/EulerScheme.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

void EulerScheme::init(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc)
{
	step(deltaTime, pos, vel, acc);
}

void EulerScheme::step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc)
{
	pos.value += vel.value * deltaTime;
	vel.value += acc.value * deltaTime;
}

