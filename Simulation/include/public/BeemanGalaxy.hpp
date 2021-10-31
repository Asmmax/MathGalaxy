#pragma once
#include "Galaxy.hpp"
#include "Vector.hpp"
#include <vector>

class BeemanGalaxy : public Galaxy
{
private:
	bool _isFirstStep;
	std::vector<Vector> _tempPositions;
	std::vector<Vector> _tempAccelerations;
public:
	BeemanGalaxy();
	void step(double deltaTime) override;
private:
	void storePositions();
	void restorePositions();

	void storeAccelerations();
	void restoreAccelerations();

	void computeAccelerations();
	void init(double deltaTime);
};
