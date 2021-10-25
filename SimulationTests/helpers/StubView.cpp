#include "StubView.hpp"

void StubView::update(int entityId, const Position& position)
{
	_positions[entityId] = position;
}

void StubView::update(int entityId, const Velocity& velocity)
{
	_velocities[entityId] = velocity;
}

void StubView::update(int entityId, const Acceleration& acceleration)
{
	_accelerations[entityId] = acceleration;
}

void StubView::removeView(int entityId)
{
	_positions.erase(entityId);
	_velocities.erase(entityId);
	_accelerations.erase(entityId);
}

const Position& StubView::getPosition(int entityId)
{
	return _positions[entityId];
}

const Velocity& StubView::getVelocity(int entityId)
{
	return _velocities[entityId];
}

const Acceleration& StubView::getAcceleration(int entityId)
{
	return _accelerations[entityId];
}
