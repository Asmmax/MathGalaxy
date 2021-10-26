#include "schemes/EulerKromerScheme.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

void EulerKromerScheme::step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc)
{
	vel.value += acc.value * deltaTime;
	pos.value += vel.value * deltaTime;
}