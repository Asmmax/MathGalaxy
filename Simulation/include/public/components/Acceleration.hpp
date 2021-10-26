#pragma once

#include "Vector.hpp"

struct Acceleration
{
	Vector value;
	Vector preValue;

	Acceleration() :
		value(Vector{0,0,0}),
		preValue(value)
	{
	}

	Acceleration(const Acceleration& acc) :
		value(acc.value),
		preValue(acc.preValue)
	{
	}

	Acceleration(double xVal, double yVal, double zVal) :
		value(Vector{ xVal,yVal,zVal }),
		preValue(value)
	{
	}

	Acceleration(const Vector& val):
		value(val),
		preValue(val)
	{
	}
};
