#pragma once
#include "IView.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include <map>

class StubView : public IView
{
private:
	std::map<int, Position> _positions;
	std::map<int, Velocity> _velocities;
	std::map<int, Acceleration> _accelerations;
public:
	void update(int entityId, const Position& position) override;
	void update(int entityId, const Velocity& velocity) override;
	void update(int entityId, const Acceleration& acceleration) override;
	void removeView(int entityId) override;

	const Position& getPosition(int entityId);
	const Velocity& getVelocity(int entityId);
	const Acceleration& getAcceleration(int entityId);
};