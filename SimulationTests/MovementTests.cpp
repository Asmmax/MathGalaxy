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

	Vector startPos{ 5,-4,3 };
	Vector startVel{ 1,2,-3 };
	Vector acc{ 2,1,1 };

	int someBody = world->createEntity();
	auto& bodyPos = world->attach(someBody, Position{ startPos });
	world->attach(someBody, Velocity{ startVel });
	world->attach(someBody, Acceleration{ acc });

	int stepCount = 1000;
	double step = 0.01;
	double time = step * stepCount;

	for (int i = 0; i < stepCount; i++) {
		simul.movement(step);
	}

	double tolerance = 2 * time * step;
	Vector newPos = startPos + startVel * time + acc / 2 * time * time;

	REQUIRE(Approx(bodyPos.value.x).margin(tolerance) == newPos.x);
	REQUIRE(Approx(bodyPos.value.y).margin(tolerance) == newPos.y);
	REQUIRE(Approx(bodyPos.value.z).margin(tolerance) == newPos.z);
}
