#pragma once

struct Acceleration;
struct Mass;
struct Position;
struct Velocity;

class IGalaxyRegistry
{
public:
	virtual ~IGalaxyRegistry() {}

	virtual int createEntity() = 0;

	virtual void attach(int entity, const Mass& mass) = 0;
	virtual void attach(int entity, const Acceleration& acc) = 0;
	virtual void attach(int entity, const Position& pos) = 0;
	virtual void attach(int entity, const Velocity& vel) = 0;
};