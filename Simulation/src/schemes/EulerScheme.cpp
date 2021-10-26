#include "schemes/EulerScheme.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

void EulerScheme::step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc)
{
	pos.value += vel.value * deltaTime;
	vel.value += acc.value * deltaTime;
}
