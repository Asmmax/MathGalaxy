#include "schemes/CentralDifferenceScheme.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

void CentralDifferenceScheme::init(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc)
{
	vel.value += acc.value * deltaTime / 2;
	pos.value += vel.value * deltaTime;
}

void CentralDifferenceScheme::step(double deltaTime, Position& pos, Velocity& vel, const Acceleration& acc)
{
	vel.value += acc.value * deltaTime;
	pos.value += vel.value * deltaTime;
}
