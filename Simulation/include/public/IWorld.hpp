#pragma once
#include <memory>

struct Acceleration;
struct Mass;
struct Position;
struct Velocity;

class IWorld 
{
public:
	virtual ~IWorld() {}

	virtual int createEntity() = 0;

	virtual void attach(int entity, const Mass& mass) = 0;
	virtual const Acceleration& attach(int entity, const Acceleration& acc) = 0;
	virtual const Position& attach(int entity, const Position& pos) = 0;
	virtual const Velocity& attach(int entity, const Velocity& vel) = 0;
};