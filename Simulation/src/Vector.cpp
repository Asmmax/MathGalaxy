#include "Vector.hpp"
#include <cmath>

double Vector::sqrLength() const
{
	return x * x + y * y + z * z;
}
double Vector::length() const
{
	return sqrt(sqrLength());
}

Vector& Vector::operator+=(const Vector& right)
{
	x += right.x;
	y += right.y;
	z += right.z;
	return *this;
}
Vector& Vector::operator-=(const Vector& right)
{
	x -= right.x;
	y -= right.y;
	z -= right.z;
	return *this;
}
Vector Vector::operator+(const Vector& right) const
{
	Vector copy{ *this };
	copy += right;
	return copy;
}
Vector Vector::operator-(const Vector& right) const
{
	Vector copy{ *this };
	copy -= right;
	return copy;
}
Vector Vector::operator*(double right) const
{
	return Vector{
	x * right,
	y * right,
	z * right
	};
}
Vector Vector::operator/(double right) const
{
	return Vector{
	x / right,
	y / right,
	z / right
	};
}
