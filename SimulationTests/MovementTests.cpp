#include "catch.hpp"
#include "IWorld.hpp"
#include "Simulation.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

TEST_CASE("All bodies must move", "[Movement]") 
{
	Simulation simul;
	IWorld* world = simul.getWorld();

	Position startPos{ 5,-4,3 };
	Velocity startVel{ 1,2,-3 };
	Acceleration acc{ 2,1,1 };

	int someBody = world->createEntity();
	auto& bodyPos = world->attach(someBody, startPos);
	world->attach(someBody, startVel);
	world->attach(someBody, acc);

	int stepCount = 1000;
	double step = 0.01;
	double time = step * stepCount;

	for (int i = 0; i < stepCount; i++) {
		simul.movement(step);
	}

	double tolerance = 2 * time * step;

	REQUIRE(Approx(bodyPos.x).margin(tolerance) == startPos.x + startVel.x * time + acc.x / 2 * time * time);
	REQUIRE(Approx(bodyPos.y).margin(tolerance) == startPos.y + startVel.y * time + acc.y / 2 * time * time);
	REQUIRE(Approx(bodyPos.z).margin(tolerance) == startPos.z + startVel.z * time + acc.z / 2 * time * time);
}
