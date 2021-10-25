#pragma once

struct Position;
struct Velocity;
struct Acceleration;

class IView
{
public:
	virtual ~IView() {}
	virtual void update(int entityId, const Position& position) = 0;
	virtual void update(int entityId, const Velocity& velocity) = 0;
	virtual void update(int entityId, const Acceleration& acceleration) = 0;
	virtual void removeView(int entityId) = 0;
};