#pragma once

struct Vector
{
	double x{0.};
	double y{0.};
	double z{0.};

	double sqrLength() const;
	double length() const;

	Vector& operator+=(const Vector& right);
	Vector& operator-=(const Vector& right);
	Vector operator+(const Vector& right) const;
	Vector operator-(const Vector& right) const;
	Vector operator*(double right) const;
	Vector operator/(double right) const;
};

inline Vector operator*(double left, const Vector& right) { return right * left; }
